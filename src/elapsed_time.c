/*
  This code performs edge detection using a Sobel filter on a video stream meant as input to a neural network
*/

//
#include "common.h"
#include "kernel.h"
#include <pthread.h>

struct arguments {
	u8 *cframe;
	u8 *oframe;
	i32 tol;
};

#if SQRT | BASELINE

void grayscale_weighted(u8 *restrict frame)
{
	f32 gray;
	for (u64 i = 0; i < H * W * 3; i += 3) {
		gray = ((float)frame[i] * 0.299) +
		       ((float)frame[i + 1] * 0.587) +
		       ((float)frame[i + 2] * 0.114);
		frame[i] = gray;
		frame[i + 1] = gray;
		frame[i + 2] = gray;
	}
}

#else
void grayscale_weighted(u8 *restrict frame)
{
	f32 gray;
	for (u64 i = 0; i < H * W * 3; i += 3) {
		gray = ((float)frame[i] * 0.299) +
		       ((float)frame[i + 1] * 0.587) +
		       ((float)frame[i + 2] * 0.114);
		frame[i / 3] = gray;
	}
}
#endif
//Convert an image to its grayscale equivalent - better color precision

void *threaded_function(void *args)
{
	struct arguments *argument = (struct arguments *)args;
	sobel_7((*argument).cframe, (*argument).oframe, (*argument).tol);
	return NULL;
}

//
int main(int argc, char **argv)
{
	//
	struct timespec begin, end;
	clock_gettime(CLOCK_MONOTONIC_RAW, &begin);
	if (argc < 3)
		return printf("Usage: %s [raw input file] [raw output file]\n",
			      argv[0]),
		       1;

	//Size of a frame
	u64 size = sizeof(u8) * H * W * 3;

	//
	f64 elapsed_s = 0.0;
	f64 elapsed_ns = 0.0;
	f64 mib_per_s = 0.0;
	struct timespec t1, t2;
	f64 samples[MAX_SAMPLES];
	//
	u64 nb_bytes = 1, frame_count = 0, samples_count = 0;

	//
	u8 *cframe = _mm_malloc(size, 32);
	u8 *oframe = _mm_malloc(size, 32);

	//
	FILE *fpi = fopen(argv[1], "rb");
	FILE *fpo = fopen(argv[2], "wb");

	//
	if (!fpi)
		return printf("Error: cannot open file '%s'\n", argv[1]), 2;

	//
	if (!fpo)
		return printf("Error: cannot open file '%s'\n", argv[2]), 2;

	//Read & process video frames

	u64 i;
	// nb_bytes = fread(cframe, sizeof(u8), H * W * 3*360, fpi);
	// #pragma omp parallel for
	// for(i = 0; i < 360; i++){
	// printf("%llu\n", i);
	// nb_bytes = fread(cframe, sizeof(u8), H * W * 3, fpi);
	// }
	while ((nb_bytes = fread(cframe, sizeof(u8), H * W * 3, fpi))) {
		//
		grayscale_weighted(cframe);

		do {
			//Start
			clock_gettime(CLOCK_MONOTONIC_RAW, &t1);

			//Put other versions here

#if BASELINE
			sobel_baseline(cframe, oframe, 100.0);
#endif
#if SOBEL3
			sobel_3(cframe, oframe, 10000.0);
#endif
#if SOBEL7
			sobel_7(cframe, oframe, 10000.0);
#endif
#if SQRT
			sobel_sqrt(cframe, oframe, 10000.0);
#endif
#if PIXEL
			sobel_pixel(cframe, oframe, 100.0);
#endif
#if PIXELSQRT
			sobel_pixelsqrt(cframe, oframe, 10000.0);
#endif
#if OMP
			sobel_omp(cframe, oframe, 10000.0);
#endif
#if THREAD
			sobel_3(cframe, oframe, 10000.0);
#endif
			//Stop
			clock_gettime(CLOCK_MONOTONIC_RAW, &t2);

			//Nano seconds
			elapsed_ns = (f64)(t2.tv_nsec - t1.tv_nsec);

		} while (elapsed_ns <= 0.0);

		//Seconds
		elapsed_s = elapsed_ns / 1e9;

		//2 arrays
		mib_per_s =
			((f64)(nb_bytes << 1) / (1024.0 * 1024.0)) / elapsed_s;

		//
		if (samples_count < MAX_SAMPLES)
			samples[samples_count++] = elapsed_ns;

		//frame number; size in Bytes; elapsed ns; elapsed s; bytes per second
		// fprintf(stdout, "%20llu; %20llu bytes; %15.3lf ns; %15.3lf MiB/s\n", frame_count, nb_bytes << 1, elapsed_ns, mib_per_s);

		// Write this frame to the output pipe
		// #pragma omp critical
		// {
		fwrite(oframe, sizeof(u8), H * W * 3, fpo);
		// }

		//
		frame_count++;
	}

	// fwrite(oframe, sizeof(u8), H * W * 3*360, fpo);
	//
	sort(samples, samples_count);

	//
	f64 min, max, avg, mea, dev;

	//
	mea = mean(samples, samples_count);

	//
	dev = stddev(samples, samples_count);

	//
	min = samples[0];
	max = samples[samples_count - 1];

	elapsed_s = mea / 1e9;

	//2 arrays (input & output)
	mib_per_s = ((f64)(size << 1) / (1024.0 * 1024.0)) / elapsed_s;

	//
	// printf("%s; %20llu bytes;  %15.3lf MiB/s; %15.3lf %%;\n",
	// argv[3],(sizeof(u8) * H * W * 3) << 1, mib_per_s,
	// (dev * 100.0 / mea));

	//
	_mm_free(cframe);
	_mm_free(oframe);

	//
	fclose(fpi);
	fclose(fpo);
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);

	printf("%s; %lf; %lf; SpeedUp : %lf\n", argv[3],
	       (end.tv_nsec - begin.tv_nsec) * 1e-9 +
		       (end.tv_sec - begin.tv_sec),
	       (t2.tv_nsec - t1.tv_nsec) + ((t2.tv_sec - t1.tv_sec) * 1e9),
	       (mib_per_s / 160));
	return 0;
}
