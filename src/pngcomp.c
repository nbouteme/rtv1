#include <unistd.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	unsigned length;
	char magic[4];
	char data[];
} png_chunk;

typedef struct
{
	int size;
	unsigned char data[];
} size_pair;

unsigned bswap_32(unsigned n)
{
	return (((n >> 24) & 0x000000FFu) |
			((n >>  8) & 0x0000FF00u) |
			((n <<  8) & 0x00FF0000u) |
			((n << 24) & 0xFF000000u));
}

unsigned adler32(unsigned char *data, size_t len)
{
    unsigned a;
	unsigned b;
    unsigned index;

	index = 0;
	a = 1;
	b = 0;
    while (index < len)
    {
        a = (a + data[index]) % 65521;
        b = (b + a) % 65521;
		++index;
    }
    return (b << 16) | a;
}

unsigned crc32(unsigned char *buf, int len)
{
	unsigned c;
	int i;
	int k;
	unsigned v;

	c = ~0;
	i = 0;
	v = 0;
	while (i < len)
	{
		c ^= buf[i];
		k = 0;
		while(k++ < 8)
		{
			v = (c & 1) ? 0xedb88320 : 0;
			c = v ^ (c >> 1);
		}
		++i;
	}
	return c ^ ~0;
}

png_chunk *make_chunk(char type[4], void *data, int size, int *osize)
{
	*osize = sizeof(png_chunk) + size + 4;
	png_chunk *ret = malloc(*osize);
	ret->length = bswap_32(size);
	memcpy(ret->magic, type, 4);
	memcpy(ret->data, data, size);
	unsigned *crcp = (void*)&((char*)ret->data)[size];
	*crcp = bswap_32(crc32((void*)&ret->magic, size + 4));
	return ret;
}

void *deflate(void *data, int s, char l)
{
	void *ret = malloc(s + 1 + 4);
	char *b = ret;
	*b = l;
	short *u = (void*)(b + 1);
	u[0] = s;
	u[1] = 0xffff ^ s;
	memcpy(&b[5], data, s);
	return ret;
}

size_pair **make_arr(unsigned char *data, int s, int c)
{
	size_pair **ret;
	int i;

	ret = calloc(sizeof(size_pair*), (s / c) + 2);
	i = 0;
	while(s > 0)
	{
		ret[i] = malloc(sizeof(size_pair) + (s >= c ? c : s));
		ret[i]->size = (s >= c ? c : s);
		memcpy(ret[i]->data, data, (s >= c ? c : s));
		data += (s >= c ? c : s);
		s -= (s >= c ? c : s);
		++i;
	}
	return ret;
}

void *zlib_stream(void *data, int s, int *osize)
{
	size_pair **seg = make_arr(data, s, 0xffff);
	char *kek[3] = {0};
	int os = 0;

	kek[2] = (void*)seg;
	while(*seg)
	{
		kek[1] = kek[0];
		kek[0] = malloc(os + (*seg)->size + 5);
		memcpy(kek[0], kek[1], os);
		free(kek[1]);
		kek[1] = deflate((*seg)->data, (*seg)->size, !seg[1]);
		memcpy(&((char*)kek[0])[os], kek[1], (*seg)->size + 5);
		free(kek[1]);
		os += (*seg)->size + 5;
		free(*seg);
		++seg;
	}
	free(kek[2]);
	kek[2] = malloc(*osize = 2 + os + 4);
	memcpy(kek[2], "\x78\x01", 2);
	memcpy(&kek[2][2], kek[0], os);
	free(kek[0]);
	*(unsigned*)&kek[2][2 + os] = bswap_32(adler32(data, s));
	return kek[2];
}

png_chunk *png_ihdr(int w, int h, int *osize)
{
	char data[4 + 4 + 5];
	int *d;

	memset(data, 0, sizeof(data));
	d = (void*)data;
	d[0] = bswap_32(w);
	d[1] = bswap_32(h);
	data[8] = 8;
	data[9] = 2;
	return make_chunk("IHDR", data, sizeof(data), osize);
}

void *png_stream(char *li, int w, int h, int os, int *osize)
{
	char *ret;
	void *chks[3];
	int t[3];

	*osize = 0;
	chks[0] = png_ihdr(w, h, t);
	ret = zlib_stream(li, os, osize);
	chks[1] = make_chunk("IDAT", ret, *osize, t + 1);
	free(ret);
	chks[2] = make_chunk("IEND", "", 0, t + 2);
	*osize = 8 + t[0] + t[1] + t[2];
	ret = malloc(*osize);
	memcpy(ret, "\x89PNG\r\n\x1a\n", 8);
	memcpy(ret + 8, chks[0], t[0]);
	memcpy(ret + 8 + t[0], chks[1], t[1]);
	memcpy(ret + 8 + t[0] + t[1], chks[2], t[2]);
	free(chks[0]);
	free(chks[1]);
	free(chks[2]);
	return ret;
}

void *to_png(int w, int h, void *data, int s, int *osize)
{
	size_pair **seg;
	char *lines[3];
	int os;

	os = 0;
	seg = make_arr(data, s, 3 * w);
	lines[0] = 0;
	lines[2] = (void*)seg;
	while(*seg)
	{
		lines[1] = lines[0];
		lines[0] = malloc(os + (*seg)->size + 1);
		memcpy(lines[0], lines[1], os);
		free(lines[1]);
		lines[1] = &lines[0][os];
		*lines[1] = 0;
		memcpy(lines[1] + 1, (*seg)->data, (*seg)->size);
		os += (*seg)->size + 1;
		free(*seg);
		++seg;
	}
	free(lines[2]);
	lines[2] = png_stream(lines[0], w, h, os, osize);
	free(lines[0]);
	return lines[2];
}
