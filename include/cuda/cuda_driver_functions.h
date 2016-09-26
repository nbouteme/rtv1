#ifndef CUDA_DRIVER_FUNCTIONS_H
# define CUDA_DRIVER_FUNCTIONS_H

# define HIDE_DRIVER_DEF
# include <core/driver_interface.h>
# undef HIDE_DRIVER_DEF

void cuda_init(t_display *self);
void cuda_genimage(t_display *disp);
void cuda_fini(t_display *self);

#endif
