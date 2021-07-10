#define SIZEX 2000
#define SIZEY 2000

long * huge_matrixA;
long * huge_matrixB;
long * huge_matrixC;

FILE *fin1, *fin2, *fout, *ftest;

void flush_all_caches();
void load_matrix_base();
void free_all();
void multiply_base();
void compare_results();

// Your job is to finish these three functions in the way that it is fast
void write_results();
void load_matrix();
void multiply();

// Any additional variables needed go here
#define BSIZE 25
#define THREAD_N 10

// Any helper functions go here
struct inner_mat_mul_arg {
    long i;
    long jj;
    long kk;
};

struct outer_mat_mul_arg {
    long jj;
    long kk;
};