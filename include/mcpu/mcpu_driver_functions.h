#ifndef MCPU_DRIVER_FUNCTIONS_H
# define MCPU_DRIVER_FUNCTIONS_H

# define HIDE_DRIVER_DEF
# include <core/driver_interface.h>
# undef HIDE_DRIVER_DEF

# ifndef SRC_CPU
#  error "This driver depends on the CPU driver"
# endif

void mcpu_init(t_driver *self);
int mcpu_genimage(t_display *disp);
void mcpu_destroy(t_driver *self);

#endif
