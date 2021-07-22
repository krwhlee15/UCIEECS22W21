#ifndef ADVANCED_H_INCLUDED_
#define ADVANCED_H_INCLUDED_

#include "Constants.h"
#include "Image.h"

/* noise filter */
IMAGE *Noise(IMAGE *image, int n);

/* posterize filter */
IMAGE *Posterize(IMAGE *image, unsigned int rbits, unsigned int gbits, unsigned int bbits);

/* negative filter */
IMAGE *NegativeFilter(IMAGE *image);

/* image crop */
IMAGE *Square(IMAGE *image, int x, int y, int L);

/* enlarge */
IMAGE *Enlarge(IMAGE *image, int percentage);

/* brightness and contrast adjustment */
IMAGE *BrightnessandContrast(IMAGE *image, int brightness, int contrast);

#endif /* ADVANCED_H_INCLUDED_ */

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
