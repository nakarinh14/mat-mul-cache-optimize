#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mm.h"



// Task 1: Flush the cache so that we can do our measurement :)
void flush_all_caches(){ 
	// https://stackoverflow.com/a/3446139
	const int size = 20*1024*1024; // Allocate 20M. Set much larger then L2
	char *c = (char *)malloc(size);
	for (int i = 0; i < 0xffff; i++)
		for (int j = 0; j < size; j++)
			c[j] = i*j;
	free(c);
}

void load_matrix_base()
{
	long i;
	huge_matrixA = malloc(sizeof(long)*(long)SIZEX*(long)SIZEY);
	huge_matrixB = malloc(sizeof(long)*(long)SIZEX*(long)SIZEY);
	huge_matrixC = malloc(sizeof(long)*(long)SIZEX*(long)SIZEY);
	// Load the input
	// Note: This is suboptimal because each of these loads can be done in parallel.
	for(i=0;i<((long)SIZEX*(long)SIZEY);i++){
		fscanf(fin1, "%ld", (huge_matrixA+i));
		fscanf(fin2, "%ld", (huge_matrixB+i));
		huge_matrixC[i] = 0;
	}
}

void free_all()
{
	free(huge_matrixA);
	free(huge_matrixB);
	free(huge_matrixC);
}

void multiply_base()
{
	long i, j, iter_idx, accum;
	for (i = 0; i < (long) SIZEY * (long) SIZEX; i+=(long)SIZEX) {
		for (j = 0; j < (long) SIZEX; j++) {
			accum = 0;
			for (iter_idx = 0; iter_idx < (long) SIZEX; iter_idx++){
				accum += huge_matrixA[i+iter_idx] * huge_matrixB[(iter_idx*(long)SIZEX)+j];
			}
			// printf("i: %ld,j: %ld => %ld\n", i, j, accum);
			huge_matrixC[i + j] = accum;
		}
	}
}

void compare_results()
{
	fout = fopen("./out.in","r");
	long i;
	long temp1, temp2;
	for(i=0;i<((long)SIZEX*(long)SIZEY);i++){
		fscanf(fout, "%ld", &temp1);
		fscanf(ftest, "%ld", &temp2);
		if (temp1 != temp2){
			printf("Wrong solution!");
			exit(1);
		}
	}
	fclose(fout);
	fclose(ftest);
}

void write_results()
{
	fout = fopen("./out.in","w");
	long i, j; 
	for (i = 0; i < ((long)SIZEX*(long)SIZEY); i+=((long)SIZEX)){
		for (j = 0; j < ((long)SIZEY); j++) {
			fprintf(fout, "%ld ", huge_matrixC[i + j]); 
		}
		fputs("\n", fout);
	}
	fclose(fout);
}

void load_matrix()
{
	long i, inner = 0, outter = 0;
	huge_matrixA = malloc(sizeof(long)*(long)SIZEX*(long)SIZEY);
	huge_matrixB = malloc(sizeof(long)*(long)SIZEX*(long)SIZEY);
	huge_matrixC = malloc(sizeof(long)*(long)SIZEX*(long)SIZEY);
	// Load the input
	// Note: This is suboptimal because each of these loads can be done in parallel.
	for(i=0;i<((long)SIZEX*(long)SIZEY);i++){
		fscanf(fin1, "%ld", (huge_matrixA + i));
		fscanf(fin2, "%ld", (huge_matrixB + inner + ((long)SIZEX*outter++)));
		if(outter == SIZEX) {
			inner++;
			outter = 0;
		}
		huge_matrixC[i] = 0;
	}
}

void multiply(){
	long i, j, k, kk, jj, i_mult, j_mult;
    long sum;
    long en = (long)(SIZEX); /* Amount that fits evenly into blocks */
	for (kk = 0; kk < en; kk += (long)BSIZE){
		for (jj = 0; jj < en; jj += (long) BSIZE) {
			for (i = 0; i < (long)SIZEX; i++) {
				i_mult = (i * (long)SIZEX);
				for (j = jj; j < jj + (long)BSIZE; j++){
					sum = huge_matrixC[i_mult + j];
					j_mult = j * (long)SIZEX;
					for (k = kk; k < kk + (long)BSIZE; k++){
						sum += huge_matrixA[i_mult + k] * huge_matrixB[k + j_mult];
					}
					huge_matrixC[i_mult + j] = sum;
				}
			}
		}
	}
}

int main()
{
	
	clock_t s,t;
	double total_in_base = 0.0;
	double total_in_your = 0.0;
	double total_mul_base = 0.0;
	double total_mul_your = 0.0;
	fin1 = fopen("./input1.in","r");
	fin2 = fopen("./input2.in","r");
	fout = fopen("./out.in","w");
	ftest = fopen("./reference.in","r");
	

	flush_all_caches();

	s = clock();
	load_matrix_base();
	t = clock();
	total_in_base += ((double)t-(double)s) / CLOCKS_PER_SEC;
	printf("[Baseline] Total time taken during the load = %f seconds\n", total_in_base);

	s = clock();
	multiply_base();
	t = clock();
	total_mul_base += ((double)t-(double)s) / CLOCKS_PER_SEC;
	printf("[Baseline] Total time taken during the multiply = %f seconds\n", total_mul_base);
	fclose(fin1);
	fclose(fin2);
	fclose(fout);
	free_all();

	fin1 = fopen("./input1.in","r");
	fin2 = fopen("./input2.in","r");
	fout = fopen("./out.in","w");
	
	flush_all_caches();

	s = clock();
	load_matrix();
	t = clock();
	total_in_your += ((double)t-(double)s) / CLOCKS_PER_SEC;
	printf("Total time taken during the load = %f seconds\n", total_in_your);

	s = clock();
	multiply();
	t = clock();
	total_mul_your += ((double)t-(double)s) / CLOCKS_PER_SEC;
	printf("Total time taken during the multiply = %f seconds\n", total_mul_your);
	write_results();
	fclose(fin1);
	fclose(fin2);

	free_all();
	compare_results();

	return 0;
}
