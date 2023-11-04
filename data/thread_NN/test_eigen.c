#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <omp.h>
#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

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

void Check_result(float *C, float *C1, long M, long N, int flag)
{

	int i, j;

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


}

int main()
{


	setNbThreads(num);
	int i, j, k, pc;
	int loop = 5;
	long M, N, K;
	double start, cost;
	double ops;
	int lda, ldb, ldc, flag;
	double total_cost = 0;
	double total_cost1 = 0;
	double start1, cost1;
	FILE *fp;
	if ( (fp = fopen("eigen_thread_NN_N32.txt", "w")) == NULL )
	{
		puts("Fail to open file!");
		exit(0);
	}

	for (j = 0 ; j < 40; j++)
	{
		M = 2048 + 256 * j;
		N = 32;
		K = 5000;

		ops = (double )M * N  * K * 1.0e-09 * 2;
		fprintf(fp, "%d %d %d", M, N, K);
		for (pc = 0; pc < 5; pc++)
		{

  			Matrix<float, Dynamic, Dynamic, RowMajor>A = MatrixXf::Random(M, K);
  			Matrix<float, Dynamic, Dynamic, RowMajor>B = MatrixXf::Random(K, N);
  			Matrix<float, Dynamic, Dynamic, RowMajor>C = MatrixXf::Random(M, N);

			for ( i = 0 ; i < 2; i++)
				C = A * B;

			start = dclock();
			for ( i = 0; i < loop ; i++)
				C = A * B;
			cost = (dclock() - start) / loop;


			printf("\nEigen:  M= %d N=%d K=%d flops = %lf effic= %.3lf %\n",
			       M, N, K, ops / cost, ops / cost / 17.6 * 100 / num);
			fprintf(fp, " %lf", ops / cost);

		}
		fprintf(fp, "\n");
	}

	fclose(fp);
	return 0;
	

}
