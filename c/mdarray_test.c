#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long** makeRaggedArray(long size) {
	long** arr = malloc(sizeof(long) * size);
	long   i, j;

	for (i = 0; i < size; i++) {
		arr[i] = malloc(sizeof(long) * i);
		for (j = 0; j < i; j++) {
			arr[i][j] = 0;
		}
	}

	return arr;
}

long* makeStraightArray(long size) {
	long* arr = malloc(sizeof(long) * size * (size + 1) / 2);
	long  i, j;

	for (i = 0; i < size; i++) {
		for (j = 0; j < i; j++) {
			arr[i * (i + 1) / 2 + j] = 0;
		}
	}
	return arr;
}

long randRaggedLookup(long** arr, long size) {
	long i = random() % size + 1;
	long j = random() % i;
	return arr[i][j]++;
}

long randStraightLookup(long* arr, long size) {
	long i      = random() % size + 1;
	long j      = random() % i;
	long lookup = i * (i + 1) / 2;
	return arr[lookup + j]++;
}

void test(int test_size) {
	int iter_size = 10000;

	printf("\tStarting allocation of ragged array.\n");
	long** arr1 = makeRaggedArray(test_size);
	printf("\tStarting allocation of stride array.\n");
	long*   arr2 = makeStraightArray(test_size);
	int     i, j;
	long    index;
	clock_t start, end;
	double  cpu_time_used;

	printf("\t\tAllocation done\n");

	printf("\tRagged Array timing test:\n");
	start = clock();
	for (i = 0; i < iter_size; i++) {
		randRaggedLookup(arr1, test_size - 1);
	}
	end           = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("\t\tRandom access:  %f\n", cpu_time_used);

	start = clock();
	for (i = 0; i < test_size; i++) {
		for (j = 0; j < i; j++) {
			arr1[i][j]++;
		}
	}
	end           = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("\t\tOrdered access: %f\n", cpu_time_used);

	printf("\tStraight Array timing test:\n");
	start = clock();
	for (i = 0; i < iter_size; i++) {
		randStraightLookup(arr2, test_size - 1);
	}
	end           = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("\t\tRandom access:  %f\n", cpu_time_used);

	start = clock();
	for (i = 0; i < test_size; i++) {
		index = (i * (i + 1)) / 2;
		for (j = 0; j < i; j++) {
			arr2[index + j]++;
		}
	}
	end           = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("\t\tOrdered access: %f\n", cpu_time_used);
}

int main(void) {

	printf("32 Elements\n");
	test(32);
	printf("64 Elements\n");
	test(64);
	printf("128 Elements\n");
	test(128);
	printf("1024 Elements\n");
	test(1024);
	printf("2048 Elements\n");
	test(2048);
	printf("4096 Elements\n");
	test(4096);
	/*  printf("8192 Elements\n");*/
	/*  test(8192);*/
	/*  printf("16384 Elements\n");*/
	/*  test(16384);*/
	/*  printf("32768 Elements\n");*/
	/*  test(32768);*/

	return 0;
}
