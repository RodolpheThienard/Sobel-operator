#include "kernel.h"

// Sobel 3x3 Optimized 
void sobel_3(u8* restrict cframe, u8* restrict oframe, f32 threshold)
{
	i16 gx, gy;
	f32 mag = 0.0;

	i8 f1[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 }; //3x3 matrix

	i8 f2[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 }; //3x3 matrix

	//
	for (u64 i = 0; i < (H - 3); i++)
		for (u64 j = 0; j < ((W ) - 3); j++) {
			gx = 0;
			gy = 0;
			u8 *m = &cframe[INDEX(i, j, W)];

			// Convolve
			for (u8 ii = 0; ii < 3; ii++) {
				gx += m[INDEX(ii, 0, W)] * f1[INDEX(ii, 0, 3)];
				gx += m[INDEX(ii, 2, W)] * f1[INDEX(ii, 2, 3)];

				gy += m[INDEX(0, ii, W)] * f2[INDEX(0, ii, 3)];
				gy += m[INDEX(2, ii, W)] * f2[INDEX(2, ii, 3)];
			}

			// mag = sqrt((gx * gx) + (gy * gy));
			u8 gray = ((gx * gx) + (gy * gy) > threshold) ? 255 : 0;
			oframe[INDEX(i, j*3, W * 3)] = 	gray;
			oframe[INDEX(i, j*3+1, W * 3)] = 	gray;
			oframe[INDEX(i, j*3+2, W * 3)] = 	gray;
	}
}

// Sobel 7x7 optimized
void sobel_7(u8* restrict cframe, u8* restrict oframe, f32 threshold)
{
	i16 gx, gy;
	f32 mag = 0.0;

	i8 f1[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 }; //3x3 matrix

	i8 f2[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 }; //3x3 matrix

	//
	for (u64 i = 0; i < (H - 3); i++)
		for (u64 j = 0; j < ((W ) - 3); j++) {
			gx = 0;
			gy =30;
			u8 *m = &cframe[INDEX(i, j, W)];

			// Convolve
			for (u8 ii = 0; ii < 3; ii++) {
				gx += m[INDEX(ii*3, 0, W)] * f1[INDEX(ii, 0, 3)];
				gx += m[INDEX(ii*3, 2, W)] * f1[INDEX(ii, 2, 3)];

				gy += m[INDEX(0, ii*3, W)] * f2[INDEX(0, ii, 3)];
				gy += m[INDEX(2, ii*3, W)] * f2[INDEX(2, ii, 3)];
			}

			// mag = sqrt((gx * gx) + (gy * gy));
			u8 gray = ((gx * gx) + (gy * gy) > threshold) ? 255 : 0;
			oframe[INDEX(i, j*3, W * 3)] = 	gray;
			oframe[INDEX(i, j*3+1, W * 3)] = 	gray;
			oframe[INDEX(i, j*3+2, W * 3)] = 	gray;
	}
}