#include "kernel.h"

// 
i32 convolve_baseline(u8 *m, i32 *f, u64 fh, u64 fw)
{
	i32 r = 0;
	for (u64 i = 0; i < fh; i++)
		for (u64 j = 0; j < fw; j++)
			r += m[INDEX(i, j, W * 3)] * f[INDEX(i, j, fw)];
	return r;
}

//
void sobel_baseline(u8 *cframe, u8 *oframe, f32 threshold)
{
	i32 gx, gy;
	f32 mag = 0.0;

	i32 f1[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 }; //3x3 matrix

	i32 f2[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 }; //3x3 matrix

	//
	for (u64 i = 0; i < (H - 3); i++)
		for (u64 j = 0; j < ((W * 3) - 3); j++) {
			gx = convolve_baseline(&cframe[INDEX(i, j, W * 3)], f1,
					       3, 3);
			gy = convolve_baseline(&cframe[INDEX(i, j, W * 3)], f2,
					       3, 3);

			mag = sqrt((gx * gx) + (gy * gy));

			oframe[INDEX(i, j, W * 3)] = (mag > threshold) ? 255 :
									 mag;
		}
}
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


void sobel_pixel(u8* restrict cframe, u8* restrict oframe, f32 threshold)
{
	i32 gx, gy;
	f32 mag = 0.0;

	i32 f1[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 }; //3x3 matrix

	i32 f2[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 }; //3x3 matrix

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
			u8 gray = (sqrt((gx * gx) + (gy * gy)) > threshold) ? 255 : 0;
			oframe[INDEX(i, j*3, W * 3)] = 	gray;
			oframe[INDEX(i, j*3+1, W * 3)] = 	gray;
			oframe[INDEX(i, j*3+2, W * 3)] = 	gray;
	}
}


void sobel_sqrt(u8 *cframe, u8 *oframe, f32 threshold)
{
	i32 gx, gy;
	f32 mag = 0.0;

	i32 f1[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 }; //3x3 matrix

	i32 f2[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 }; //3x3 matrix

	//
	for (u64 i = 0; i < (H - 3); i++)
		for (u64 j = 0; j < ((W * 3) - 3); j++) {
			gx = convolve_baseline(&cframe[INDEX(i, j, W * 3)], f1,
					       3, 3);
			gy = convolve_baseline(&cframe[INDEX(i, j, W * 3)], f2,
					       3, 3);

			mag = (gx * gx) + (gy * gy);

			oframe[INDEX(i, j, W * 3)] = (mag > threshold) ? 255 : 0;
		}
}


void sobel_pixelsqrt(u8* restrict cframe, u8* restrict oframe, f32 threshold)
{
	i32 gx, gy;
	f32 mag = 0.0;

	i32 f1[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 }; //3x3 matrix

	i32 f2[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 }; //3x3 matrix

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

			u8 gray = ((gx * gx) + (gy * gy) > threshold) ? 255 : 0;
			oframe[INDEX(i, j*3, W * 3)] = 	gray;
			oframe[INDEX(i, j*3+1, W * 3)] = 	gray;
			oframe[INDEX(i, j*3+2, W * 3)] = 	gray;
		}
}