#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <math.h>

#include <time.h>

#define POP_SIZE 1000
#define PAIRS 500
#define GENERATIONS 50
#define MUTATIONS 100

typedef struct {
	const double min;
	const double max;
	const double step;
	const size_t count;
} range_t;

typedef struct {
	range_t X;
	range_t Y;
} grid_t;

typedef struct {
	unsigned x;
	unsigned y;
	grid_t* grid;
} grid_point_t;

range_t range(const double min, const double max, const size_t count) {
	return (range_t) {min, max, (max - min) / (double) (count - 1), count};
}

double value(const unsigned n, const range_t range) {
	return range.min + n * range.step;
}

grid_t grid(const range_t X, const range_t Y) {
	return (grid_t) {X, Y};
}

grid_point_t grid_point(const unsigned x, const unsigned y, grid_t* grid) {
	return (grid_point_t) {x, y, grid};
}

grid_point_t rand_grid_point(grid_t* grid) {
	return (grid_point_t) {rand() % grid->X.count, rand() % grid->Y.count, grid};
}

double eval(double f(const double x, const double y), const grid_point_t point) {
	return f(value(point.x, point.grid->X), value(point.y, point.grid->Y));
}

void fprint_point(FILE* f, const grid_point_t point) {
	fprintf(f, "%e %e\n", value(point.x, point.grid->X), value(point.y, point.grid->Y));
}

void mutate(grid_point_t* point) {
	point->x = point->x ^ rand() % point->grid->X.count;
	point->y = point->y ^ rand() % point->grid->Y.count;
}

grid_point_t cross(const grid_point_t a, const grid_point_t b) {
	grid_point_t child;
	if (rand() % 2) {
		child.x = a.x;
		child.y = b.y;
	} else {
		child.x = b.x;
		child.y = a.y;
	}
	child.grid = a.grid;
	return child;
}

double f(const double x, const double y) {
//	return cosh(sqrt(x*x + y*y)) - 200*exp(-((x - 2)*(x - 2) + (y - 1) * (y - 1)));
//	return cos(x*x + y*y) * exp(-0.5*(x*x + y*y));
	return (x - 1) * (x - 1);
}

int compare(const void* p_1, const void* p_2) {
	if (eval(f, *(grid_point_t*) p_1) > eval(f, *(grid_point_t*) p_2)) {
		return 1;
	} else {
		return -1;
	}
}

int main(int argc, char* argv[]) {
	srand((unsigned) time(NULL));

	range_t X = range(-2, 2, 10000);
	range_t Y = range(-2, 2, 10000);
	
	grid_t main_grid = grid(X, Y);

	grid_point_t* points = (grid_point_t*) malloc((size_t) (POP_SIZE + PAIRS) * sizeof(grid_point_t));

	for (size_t i = 0; i < POP_SIZE + PAIRS; ++i) {
		points[i] = rand_grid_point(&main_grid);
	}

	for (size_t n = 0; n < GENERATIONS; ++n) {

		for (size_t i = 0; i < MUTATIONS; ++i) {
			mutate(&points[POP_SIZE + rand() % PAIRS]);
		}

		for (size_t i = 0; i < PAIRS; ++i) {
			points[POP_SIZE + i] = cross(points[rand() % POP_SIZE], points[rand() % POP_SIZE]);
		}
		
		qsort(points, POP_SIZE + PAIRS, sizeof(grid_point_t), compare);
	}
	
	for (size_t i = 0; i < POP_SIZE; ++i) {
		fprint_point(stdout, points[i]);
	}
	
	free(points);
	return EXIT_SUCCESS;
}