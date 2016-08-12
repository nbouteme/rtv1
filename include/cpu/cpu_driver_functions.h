#ifndef CPU_DRIVER_FUNCTIONS_H
# define CPU_DRIVER_FUNCTIONS_H

# define HIDE_DRIVER_DEF
# include <core/driver_interface.h>
# undef HIDE_DRIVER_DEF

void cpu_init(t_driver *self);
void cpu_genimage(t_driver *self, t_display *disp);
void cpu_destroy(t_driver *self);

#endif
