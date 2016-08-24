#ifndef UTILS_H
# define UTILS_H

typedef int (*t_check_fun)(char *s, int size);
void *from_file(const char *fn, unsigned long *size, t_check_fun check);

#endif
