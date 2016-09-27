#include <core/core.h>
#include <unistd.h>

void init_png_res(t_display *d)
{
	d->disp_internal = 0;
	d->disp_param = ft_memalloc(sizeof(float) * 3 * 1280 * 720);
	if (d->renderer_driver->init)
		d->renderer_driver->init(d);
}

void *to_png(int w, int h, void *data, int s, int *osize);

int gen_png(t_display *d)
{
	int size;
	void *image;
	int i;

	d->renderer_driver->genimage(d);
	size = 3 * 1280 * 720;
	char *pixbuf;

	pixbuf = malloc(sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		pixbuf[i] = ((float*)d->disp_param)[i] * 255;
		++i;
	}
	image = to_png(1280, 720, pixbuf, size, &size);
	write(1, image, size);
	close(1);

	return false;
}

void init_png(t_display *d)
{
	d->init = init_png_res;
	d->draw = gen_png;
	d->fini = 0;
}