// Tyler Taormina - taormina@pdx.edu
// CS333 Matrix Multiplication Video Activities
// Multi Threading with Dynamic Work Allocation

//gcc -g -Wall -o mm4 mm4.c -pthread

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/time.h>
#include <pthread.h>


#ifndef MAX_DIM
# define MAX_DIM 4000
#endif // MAX_DIM
       
#ifndef DEF_DIM
# define DEF_DIM 1000
#endif // DEF_DIM

# define MICROSECONDS_PER_SECOND 1000000.0

static float **matrix1 = NULL;
static float **matrix2 = NULL;
static float **result = NULL;
static int dim = DEF_DIM;
static int num_threads = 1;

float **alloc_matrix(void);
void free_matrix(float **);
void init(float **, float **, float **);
void output_mat(float **);
void *mult(void *);
double elapse_time(struct timeval *, struct timeval *);
int get_next_row(void);


float **
alloc_matrix(void)
{
    int i;

    float **mat = malloc(dim * sizeof(float *));
    i = -1;

    for (i = 0; i < dim; i++) {
        mat[i] = malloc(dim * sizeof(float));
    }
    return mat;
}

void 
free_matrix(float **mat)
{
    int i;

    i = -1;
    for (i = 0; i < dim; i++) {
        free(mat[i]);
    }
    free(mat);
}

void 
init(float **mat1, float **mat2, float **res)
{
    int i = -1;
    int j = -1;

    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            mat1[i][j] = (i + j) * 2.0;
            mat2[i][j] = (i + j) * 3.0;
            res[i][j] = 0.0;
        }
    }
}

void 
output_mat(float **mat)
{
    FILE *op = NULL;
    int i = -1;
    int j = -1;

#define FILE_NAME "mm4.txt"
    op = fopen(FILE_NAME, "w");
    if (op == NULL) {
        perror("could not open file: " FILE_NAME);
        exit(17);
    }
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            fprintf(op, "%8.2f ", mat[i][j]);
        }
        fprintf(op, "\n");
    }
    fclose(op);
}

double
elapse_time(struct timeval *t0, struct timeval *t1)
{
    double et = (((double) (t1->tv_usec - t0->tv_usec))
            / MICROSECONDS_PER_SECOND)
        + ((double) (t1->tv_sec - t0->tv_sec));
    return et;
}

void *
mult(void *vid)
{
    int i = -1;
    int j = -1;
    int k = -1;

    for (i = get_next_row(); i < dim; i = get_next_row()) {
        for (j = 0; j< dim; j++) {
            for (k = 0; k < dim; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    pthread_exit(EXIT_SUCCESS);
}

int
get_next_row(void)
{
    static int next_row = 0;
    static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    int cur_row = 0;

    pthread_mutex_lock(&lock);
    cur_row = next_row++;
    pthread_mutex_unlock(&lock);

    return cur_row;
}

int 
main(int argc, char **argv)
{
    struct timeval et0;
    struct timeval et1;
    struct timeval et2;
    struct timeval et3;
    struct timeval et4;
    struct timeval et5;

    pthread_t *threads = NULL;
    long tid = 0;

    {
        int opt = -1;
        while ((opt = getopt(argc, argv, "t:d:h")) != -1) {
            switch (opt) {
                case 't': 
                    num_threads = atoi(optarg);
                    // ignore for now
                    break;

                case 'd':
                    dim = atoi(optarg);
                    if (dim < DEF_DIM) {
                        dim = DEF_DIM;
                    }
                    if (dim > MAX_DIM) {
                        dim = MAX_DIM;
                    }
                    break;

                case 'h':
                    printf("%s: -t # -d #\n", argv[0]);
                    printf("\t-t #: number of threads\n");
                    printf("\t-d #: size of matrix\n");
                    exit(0);
                    break;

                default: /* '?' */
                    exit(EXIT_FAILURE);
                    break;
            }
        }
    }

    gettimeofday(&et0, NULL);
    matrix1 = alloc_matrix();
    matrix2 = alloc_matrix();
    result = alloc_matrix();
    gettimeofday(&et1, NULL);

    init(matrix1, matrix2, result);
    threads = malloc(num_threads * sizeof(pthread_t));

    gettimeofday(&et2, NULL);
    for (tid = 0; tid < num_threads; tid++) {
        pthread_create(&threads[tid], NULL, mult, (void *) tid);
    }

    for (tid = 0; tid < num_threads; tid++) {
        pthread_join(threads[tid], NULL);
    }

    //mult();
    gettimeofday(&et3, NULL);

    output_mat(result);

    gettimeofday(&et4, NULL);
    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(result);
    free(threads);

    matrix1 = matrix2 = result = NULL;
    threads = NULL; 
    gettimeofday(&et5, NULL);

    {
        double total_time = elapse_time(&et0, &et5);
        double alloc_time = elapse_time(&et0, &et1);
        double init_time = elapse_time(&et1, &et2);
        double comp_time = elapse_time(&et2, &et3);
        double op_time = elapse_time(&et3, &et4);
        double td_time = elapse_time(&et4, &et5);

        printf("Total time: %8.2lf\n", total_time);
        printf("  Alloc time: %8.2lf\n", alloc_time);
        printf("  Init  time: %8.2lf\n", init_time);
        printf("  Comp  time: %8.2lf\n", comp_time);
        printf("  O/P   time: %8.2lf\n", op_time);
        printf("  T/D   time: %8.2lf\n", td_time);
    }

    return EXIT_SUCCESS;
}
