#include <stdio.h>
#include <cblas.h>
#include <sys/time.h>
#include <stdlib.h>
#include <omp.h>
#include "LibShalom.h"


#define num 64
static double gtod_ref_time_sec = 0.0;

double dclock()
{
        double the_time, norm_sec;
        struct timeval tv;

        gettimeofday( &tv, NULL );

        if ( gtod_ref_time_sec == 0.0 )
                gtod_ref_time_sec = ( double ) tv.tv_sec;

        norm_sec = ( double ) tv.tv_sec - gtod_ref_time_sec;
        the_time = norm_sec + tv.tv_usec * 1.0e-6;
        return the_time;
}

void random_matrix( int m, int n, float *a)
{
        double drand48();

        #pragma omp parallel for num_threads(num)
        for (int i = 0 ; i < m * n; i ++)
                a[i] = 2.0 * (float)drand48( ) - 1.0 + 0.0000001 * (i / m);

}

int main()
{

        openblas_set_num_threads(1);
        LibShalom_set_thread_nums(num);
        int i, j, k, jj;
        int loop = 5;
        long M, N, K;
        double start, cost;
        double gflops;
        long lda, ldb, ldc;
        float temp = -1;
        int pc = 0;

        long Me[] = {64,    64,   64,   256,  64,   64,   128,  128,  512, 512, 128, 256,  256,  1024, 1024, 256,  512,  512,  2048, 2048, 512};
        long Ne[] = {12544, 3136, 3136, 3136, 3136, 3136, 3136, 784,  784, 784, 784, 784,  196,  196,  196,  196,  196,  49,   49,   49,   49};
        long Ke[] = {147,   64,   576,  64,   256,  576,  256,  1152, 128, 256, 512, 1152, 2304, 256,  512,  1024, 1024, 4608, 512,  1024, 2048};

        FILE *fp;

        if ( (fp = fopen("LibShalom_resnet.txt", "w+")) == NULL )
        {
                puts("Fail to open file!");
                exit(0);
        }



        for (jj = 0 ; jj < 21 ; jj ++)
        {

                M = Me[jj];
                N = Ne[jj];
                K = Ke[jj];

                double ops = (double) M * N * K * 1.0e-09 * 2;
                fprintf(fp, "%d %d %d", M, N, K);

                for (pc = 0; pc < 5; pc++)
                {
                        float *A, *B, *C, *D, *C1;
                        int flag = 0 ;
                        lda = K;
                        ldb = N;
                        ldc = N;

                        A = ( float * ) malloc( K * M * sizeof( float ) );
                        B = ( float * ) malloc( K * N * sizeof( float ) );
                        C = ( float * ) malloc( M * N * sizeof( float ) );
                        C1 = ( float * ) malloc( M * N * sizeof( float ) );

                        random_matrix(M, K, A);
                        random_matrix(K, N, B);

                        printf("M= %d, N= %d, K=%d\n", M, N, K);

                        for ( i = 0 ; i < 2; i++)
                                LibShalom_sgemm_mp(0, 0, C, A, B, M, N, K);

                        start = dclock();
                        for ( i = 0; i < loop ; i++)
                                LibShalom_sgemm_mp(0, 0, C, A, B, M, N, K);
                        cost = (dclock() - start) / loop;

                        fprintf(fp, " %.3f", ops / cost);
                        printf("\nLibShalom:  M= %d N=%d K=%d flops = %lf effic= %.3lf %\n",
                               M, N, K, ops / cost, ops / cost / 17.6 * 100 / num);



                        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K,
                                    1.0, A, lda, B, ldb, 0.0, C1, ldc);

                        for ( i = 0; i < M; i++)
                        {
                                for ( j = 0 ; j < N; j++)
                                {
                                        if ((C[i * N + j] - C1[i * N + j] > 0.001 || C[i * N + j] - C1[i * N + j] < -0.001))
                                        {
                                                printf("i = %d, j= %d\n", i , j );
                                                printf("C= %lf , C1= %lf\n", C[i * N + j], C1[i * N + j]);
                                                flag = 1;
                                                printf("error\n");
                                                break;
                                        }
                                }
                                if (flag == 1)
                                        break;
                        }

                        if (flag == 0)
                                printf("结果正确\n");


                        free(A);
                        free(B);
                        free(C);
                        free(C1);

                }
                fprintf(fp, "\n");
        }

        fclose(fp);
        return 0;

}