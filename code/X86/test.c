//杨维铃 2023.10.25

#include<stdio.h>
#include<sys/time.h>
#include <stdlib.h>
#include <cblas.h>
#include <omp.h>
#include <math.h>
#include "PACK_x86.h"
#include "kernel.h"

#define NUM 24
static double gtod_ref_time_sec = 0.0;

#define GEMM_K 512
#define GEMM_M 512
#define GEMM_N 4096

void Check_result(float *C, float *C1, long M, long N)
{

	int i, j, flag = 0;

	for( i= 0; i< M; i++)
	{
		for( j= 0 ;j < N;j++)
		{
			if(fabs(C[i * N + j] -C1[i * N + j])> 1.0e-3)
			{
					printf("i = %d, j= %d\n",i ,j );
					printf("C= %lf , C1= %lf\n", C[i*N+j], C1[i*N+j]);
					flag =1;
					printf("error\n");
					break;
			}
		}
			if(flag ==1)
				break;
	}

	if(flag == 0)
		printf("结果正确\n");

}

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
  int i,j;

  for ( i = 0; i < m; i++ )
    for ( j = 0; j < n; j++ )
		a[i * n + j]= 2.0 * (float)drand48( ) - 1.0;
}

void random_matrix1( int m, int n, float *a)
{
  double drand48();
  int i,j;

  for ( i = 0; i < m; i++ )
    for ( j = 0; j < n; j++ )
		a[i * n + j]= 1;
}


void Libshalom_SGEMM(float *C, float *A, float * B, long M, long N, long K)
{

	int Nb = N / NUM;
	void *ptr;
	float *Ac = ( float * ) malloc( K* M * sizeof( float ) );
	posix_memalign(&ptr, 64, NUM * GEMM_K * 32 *sizeof( float ));
	float *Bc = (float*)ptr;


	long Num_K_block = K / GEMM_K;
	long Edge_K = K % GEMM_K;
	long Num_M_block = M / 12;
	long Edge_M = M % 12;
	long Num_blocks0 = Num_K_block * Num_M_block;
	if(Edge_M > 0)
	{
		Num_blocks0 = Num_blocks0 + Num_K_block;
		Num_M_block = Num_M_block + 1;
	}
	long Num_blocks = Num_blocks0; 
	if(Edge_K > 0)
	{
		Num_blocks = Num_blocks0 + Num_M_block;
	}

	#pragma omp parallel num_threads(NUM)
	{
		int i, j, k, ii, jj, kk, mc, nc, kc, mr, nr;
		int size_block_m;
		int id = omp_get_thread_num();
		float *temp_Bc = Bc + id * GEMM_K * 32;


		for( i = id; i < Num_blocks; i = i + NUM)
		{
			long start_M = (i % Num_M_block) * 12;					// note
			long start_K = (i / Num_M_block) * GEMM_K;			// note
			size_block_m = 12;

			float *AA = A + start_M * K + start_K;        		// address
			float *AAc; 

			if(Edge_M > 0 && (i % Num_M_block)==(Num_M_block-1))
			{
				size_block_m = Edge_M;
			}

			if( Edge_K > 0 && i >= Num_blocks0)
			{
				AAc = Ac + start_K * M + start_M * Edge_K;  // note
				NPACK(AA, AAc, size_block_m, Edge_K, K);
			}
			else
			{
				AAc = Ac + start_K * M + start_M * GEMM_K;  // note
				NPACK(AA, AAc, size_block_m, GEMM_K, K);
			}
		}
	

		#pragma omp barrier

		for(kk = 0; kk < K; kk = kk + kc)
		{
			kc = GEMM_K;
			if(K - kk < GEMM_K)
				kc = K -kk;

			float *temp_A = Ac + kk * M;

			for(j = 0; j < Nb; j = j + nr)
			{
				nr = 32;
				if(Nb - j < 32)
					nr = Nb - j;
				float *temp_C = C + id *  Nb + j;
				float *temp_B = B + kk * N + id *  Nb + j;
				if(nr == 32)
					SMM_NN_KERNEL12x32(temp_C, temp_A, temp_B, M, Nb, kc, N, K, temp_Bc, kk);
				else if(nr == 16)
					SMM_NN_KERNEL12x16(temp_C, temp_A, temp_B, M, Nb, kc, N, K, temp_Bc, kk);
			}
		}
	}

	free(Ac);
	free(Bc);

}

int main()
{

	openblas_set_num_threads(NUM);

	int i,j,k,jj,pc;
	int loop = 20;
	long M, N, K;
	double start, cost;
	double gflops;
	long lda,ldb,ldc;
	int flag = 0;

 	FILE *fp;
	if( (fp=fopen("Libshalom_X86_NGM.txt","w")) == NULL )
	{
	  puts("Fail to open file!");
	  exit(0);
	}

	for(j = 1; j < 33; j++)
	{
		M = 16 * j;
		N = 9600;
		K = 9600;
		lda = K;
		ldb = N;
		ldc = N;
		double ops = (double) M *N *K * 1.0e-09 * 2;

		float *A = ( float * ) malloc( M * K * sizeof( float ) );
		float *B = ( float * ) malloc( K * N  * sizeof( float ) );
		float *Bc = ( float * ) malloc( K * N  * sizeof( float ) );
		float *C = ( float * ) malloc( M * N * sizeof( float ) );
		float *C1 = ( float * ) malloc( M * N * sizeof( float ) );

		random_matrix(M,K,A);
		random_matrix(K,N,B);

		Libshalom_SGEMM(C, A, B, M, N, K);

		start = dclock();
		for( i= 0; i< loop ;i++)
		{
			Libshalom_SGEMM(C, A, B, M, N, K);
		}
		cost = (dclock() - start) / loop;

		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, 
							1.0, A, lda, B, ldb, 0.0, C1, ldc);

		Check_result(C, C1, M, N);


		printf("\nLibshalom:  M= %d N=%d K=%d flops = %lf effic= %.3lf %\n", 
				M, N, K, ops/cost, ops/cost/(2 * 64) * 100/NUM);
		fprintf(fp, " %.3f", ops/cost);
		fprintf(fp, "\n");
		free(A);
		free(B);
		free(C);
		free(Bc);
		free(C1);
	}
	fclose(fp);

  return 0;

}