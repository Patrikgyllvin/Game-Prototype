#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <cmath>

#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288   /* pi */
#endif

#define DEGTORAD(n) ((n) * (M_PI / 180.0))
#define RADTODEG(n) ((n) * (180.0 / M_PI))

#endif