#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mm.h"



// Task 1: Flush the cache so that we can do our measurement :)
void flush_all_caches()
{
	free_all();
	huge_matrixA = malloc(sizeof(long)*(long)SIZEX*(long)SIZEY);
	huge_matrixB = malloc(sizeof(long)*(long)SIZEX*(long)SIZEY);
	huge_matrixC = malloc(sizeof(long)*(long)SIZEX*(long)SIZEY);
	free_all();
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
	char buffer[sizeof(long)]; 
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
	long i;
	huge_matrixA = malloc(sizeof(long)*(long)SIZEX*(long)SIZEY);
	huge_matrixB = malloc(sizeof(long)*(long)SIZEX*(long)SIZEY);
	huge_matrixC = malloc(sizeof(long)*(long)SIZEX*(long)SIZEY);
	// Load the input
	// Note: This is suboptimal because each of these loads can be done in parallel.
	if(fin1 == NULL) {
		printf("nope\n");
	}

	for(i=0;i<((long)SIZEX*(long)SIZEY);i++)
	{
		printf("%ld", i);
		fscanf(fin1, "%ld", (huge_matrixA + i));
		fscanf(fin2,"%ld", (huge_matrixB+i)); 		
		huge_matrixC[i] = 0;		
	}
}

void multiply(){
// 	int i, j, k, kk, jj;
//     double sum;
//     int en = BSIZE * (SIZEX/BSIZE); /* Amount that fits evenly into blocks */
  
//     for (i = 0; i < n; i++)
// 		for (j = 0; j < n; j++)
// 			C[i][j] = 0.0;

//     for (kk = 0; kk < en; kk += BSIZE) { 
// 		for (jj = 0; jj < en; jj += BSIZE) {
// 			for (i = 0; i < SIZEX; i++) {
// 				for (j = jj; j < jj + BSIZE; j++) {
// 					sum = C[i][j];
// 					for (k = kk; k < kk + BSIZE; k++) {
// 						sum += huge_matrixA[i][k]*B[k][j];
// 					}
// 					C[i][j] = sum;
// 				}
// 			}
// 		}
// 	/* $end bmm-ijk */
// 	/* Now finish off rest of j values  (not shown in textbook) */
// 		for (i = 0; i < SIZEX; i++) {
// 			for (j = en; j < SIZEX; j++) {
// 				sum = C[i][j];
// 				for (k = kk; k < kk + BSIZE; k++) {
// 					sum += A[i][k]*B[k][j];
// 				}
// 				C[i][j] = sum;
// 			}
// 		}
//     }

//     /* Now finish remaining k values (not shown in textbook) */ 
//     for (jj = 0; jj < en; jj += BSIZE) {
// 		for (i = 0; i < SIZEX; i++) {
// 			for (j = jj; j < jj + BSIZE; j++) {
// 			sum = C[i][j];
// 			for (k = en; k < SIZEX; k++) {
// 				sum += A[i][k]*B[k][j];
// 			}
// 			C[i][j] = sum;
// 			}
// 		}
//     }
    
//     /* Now finish off rest of j values (not shown in textbook) */
//     for (i = 0; i < SIZEX; i++) {
// 		for (j = en; j < SIZEX; j++) {
// 			sum = C[i][j];
// 			for (k = en; k < SIZEX; k++) {
// 			sum += A[i][k]*B[k][j];
// 			}
// 			C[i][j] = sum;
// 		}
//     }
//     /* $begin bmm-ijk */
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
	// free_all();

	// flush_all_caches();

	// s = clock();
	// load_matrix();
	// t = clock();
	// total_in_your += ((double)t-(double)s) / CLOCKS_PER_SEC;
	// printf("Total time taken during the load = %f seconds\n", total_in_your);

	// s = clock();
	// multiply();
	// t = clock();
	// total_mul_your += ((double)t-(double)s) / CLOCKS_PER_SEC;
	// printf("Total time taken during the multiply = %f seconds\n", total_mul_your);
	write_results();
	// fclose(fin1);
	// fclose(fin2);
	// fclose(fout);
	// free_all();
	compare_results();

	return 0;
}
