#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <math.h>

#include <time.h>

typedef struct {
	const double min;
	const double max;
} range_t;

range_t range(const double min, const double max) {
	return (range_t) {min, max};
}

double f(const double x, const double y) {
//	return cosh(sqrt(x*x + y*y)) - 200*exp(-((x - 2)*(x - 2) + (y - 1) * (y - 1)));
//	return cos(x*x + y*y) * exp(-0.5*(x*x + y*y));
	return (x - 1) * (x - 1) + (y - 1) * (y - 1);
}

double random_point(const range_t x) {
	return x.min + (rand() % RAND_MAX) * (x.max - x.min) / (double) (RAND_MAX - 1);
}

void test(double f(const double x, const double y), const range_t X, const range_t Y, const size_t N) {
	double x = random_point(X);
	double y = random_point(Y);
	double x_new, y_new;
	for (size_t n = 1; n < N + 1; ++n) {
		x_new = random_point(X);
		y_new = random_point(Y);
		if (f(x, y) > f(x_new, y_new)) {
			x = x_new;
			y = y_new;
		}
	}
	printf("%lu %le %le %le\n", N, x, y, f(x, y));
}

int main(int argc, char* argv[]) {
	srand((unsigned) time(NULL));

	range_t x = range(-5, 5);
	range_t y = range(-5, 5);
	
	for (size_t n = 1; n < 40001; ++n) {
		test(f, x, y, n);
	}
	
	return EXIT_SUCCESS;
}