#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#define PI 3.1415
FILE *input, *output;
char InPath[] = "/tmp/math.txt";
char OuPath[] = "/tmp/result.txt";
int q = 1;

int *quantity;

typedef struct iter_st {
	int loopI;
	int taylorI;
	int constN;
	int value;
} iter_t;

double power(double value, int in) {
	int i;
	double result = 1;
	for (i = 1; i <= abs(in); i++) {
		result *= value / i;
	}
	return result;
}

int powerEco(int in) {
	if ((in % 2) == 0) {
		return 1;
	} else {
		return -1;
	}
}

void* taylorStep(void *args) {
	iter_t *arg = (iter_t*) args;
	double perem = powerEco(arg->taylorI) * power(2 * PI * arg->loopI / arg->constN, 2 * arg->taylorI + 1);
	fprintf(stdout, "thread: %d; arr[%d]=%.25f\n", (int) pthread_self(), arg->loopI, perem);
	fprintf(input, "%d %d %.8lf\n", (int) pthread_self(), arg->loopI, perem);
	quantity[arg->value] = 0;
	free(arg);
	pthread_exit(NULL);
}

int taylorFunc(int steps, int values) {
	input = fopen(InPath, "w+");
	pthread_t thread[q];
	int processes = 0;
	int value = 0;
	for (int i = 0; i < q; i++) {
		quantity[i] = 0;
	}
	for (int loopI = 0; loopI < values; loopI++) {
		for (int taylorI = 0; taylorI < steps; taylorI++) {
			if (processes == q) {
				int flag = 0;
				for (;;) {
					for (int s = 0; s < q; s++) {
						if (quantity[s] == 0) {
							flag = 1;
							break;
						}
					}
					if (flag != 0) {
						break;
					}
				}
				processes--;
			}
			for (int s = 0; s < q; s++) {
				if (quantity[s] == 0) {
					value = s;
					quantity[s] = 1;
					break;
				}
			}
			iter_t *ar = (iter_t*) malloc(sizeof(iter_t));
			ar->loopI = loopI;
			ar->taylorI = taylorI;
			ar->constN = values;
			ar->value = value;
			pthread_create(&thread[value], NULL, taylorStep, ar);
			processes++;
		}
	}
	for (int i = 0; i < q; i++) {
		pthread_join(thread[i], NULL);
	}
	output = fopen(OuPath, "w");
	double *result = alloca(sizeof(double) * values);
	memset(result, 0, sizeof(double) * values);
	rewind(input);
	int pidd, f;
	double member_value;
	for (int i = 0; i < values * steps; i++) {
		fscanf(input, "%d %d %lf", &pidd, &f, &member_value);
		result[f] += member_value;
	}
	for (int i = 0; i < values; i++) {
		fprintf(output, "y[%d]=%.8lf\n", i, result[i]);
	}
	fclose(input);
	fclose(output);
	return 0;
}

int main(int argc, char *argv[]) {
	int values, steps;
	if (argc < 3) {
		fprintf(stderr, "Error:Too few arguments!\n");
		return 1;
	}
	steps = atoi(argv[1]);
	values = atoi(argv[2]);
	quantity = calloc(1, sizeof(int));
	taylorFunc(steps, values);
	free(quantity);
	return 0;
}