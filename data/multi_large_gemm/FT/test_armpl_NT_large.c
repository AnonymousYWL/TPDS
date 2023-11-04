#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <omp.h>
#include <armpl.h>


#define num 1
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

  //#pragma omp parallel for num_threads(num)
  for(int i =0 ; i < m * n; i ++)
  	a[i]= 2.0 * (float)drand48( ) - 1.0 + 0.0000001 * (i/m);

}


void random_matrix1( int m, int n, float *a)
{

  #pragma omp parallel for num_threads(num)
  for(int i =0 ; i < m * n; i ++)
  {
  	a[i] = 1.0;
  }
}


void transpose( int m, int n, float *a)
{
	float *temp_a = ( float * ) malloc( m* n * sizeof( float ) );

	int i, j;

	for( i =0 ;i< m; i++)
	{
		for( j= 0;j < n; j++)
		{
			temp_a[j * m + i] = a[i*n + j];
		}
	}


	for( i =0 ; i< n; i++)
	{
		for( j =0; j< m; j++)
		{
			a[ i * m+j] = temp_a[i*m+j];
		}
	}

	free(temp_a);
}

void Check_result(float *C, float *C1, long M, long N, int flag)
{

	int i, j;

		for( i= 0; i< M; i++)
		{
			for( j= 0 ;j < N;j++)
			{
				if((C[i*N+j]- C1[i*N+j] > 0.01 || C[i*N+j]- C1[i*N+j] < -0.01))
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


int main()
{

	omp_set_num_threads(num);
	int i,j,k,pc;
	int loop = 3;
	double start, cost=0;
	double ops;
	int lda, ldb, ldc, flag;
	double total_cost=0;
	double total_cost1=0;
	double start1, cost1;
	int M, N, K;
	float alpha=1.0;
	float beta=0.0;

	char tran = 'N';
  char trant = 'T';

	FILE *fp;
	if( (fp=fopen("armpl_NT_large_FT.txt","w")) == NULL )
	{
		puts("Fail to open file!");
		exit(0);
	}

	//start1 = dclock();
	for (j = 0 ; j < 19; j++)
	{

		M = 1200 + 600 * j;
		N = 1200 + 600 * j;
		K = 1200 + 600 * j;

		lda = M;
		ldb = N;
		ldc = M;

		ops = (double )M * N  * K * 1.0e-09 * 2;
		fprintf(fp, "%d %d %d", M, N, K);
		for(pc = 0; pc < 1; pc++)
		{

			flag = 0;

			float *A = ( float * ) malloc( K*M* sizeof( float ) );  
			float *B = ( float * ) malloc( K* N * sizeof( float ) );
			float *C = ( float * ) malloc( M* N * sizeof( float ) );
			//flush = ( float * ) malloc( 5000* 5000 * sizeof( float ) );

			//random_matrix(M,N,C);
			random_matrix(M,K,A);
			random_matrix(K,N,B);


			for( i =0 ;i< 1; i++)
			 sgemm_(&tran, &trant, &M, &N, &K, &alpha, A, &lda, B, &ldb, &beta, C, &ldc);

			//printf("Tn= %d\n", Tn);
			start = dclock();
			for( i= 0; i< loop ;i++)
				sgemm_(&tran, &trant, &M, &N, &K, &alpha, A, &lda, B, &ldb, &beta, C, &ldc);
			cost =(dclock()-start)/loop; 


			printf("\narmpl:  M= %d N=%d K=%d flops = %lf effic= %.3lf %\n", 
			M, N, K, ops/cost, ops/cost/17.6 * 100/num);
			fprintf(fp, " %lf", ops/cost);

			//random_matrix1(5000,5000,flush);
			free(A);
			free(B);
			free(C);
			//free(flush);

	  }
	  fprintf(fp, "\n");
	}

  fclose(fp);
  return 0;

}
