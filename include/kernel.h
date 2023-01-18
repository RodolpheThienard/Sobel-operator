#include "common.h"

void sobel_7(u8* restrict cframe, u8* restrict oframe, f32 threshold);
void sobel_3(u8* restrict cframe, u8* restrict oframe, f32 threshold);
void sobel_baseline(u8* restrict cframe, u8* restrict oframe, f32 threshold);
void sobel_pixel(u8* restrict cframe, u8* restrict oframe, f32 threshold);
void sobel_sqrt(u8* restrict cframe, u8* restrict oframe, f32 threshold);
void sobel_pixelsqrt(u8* restrict cframe, u8* restrict oframe, f32 threshold);
