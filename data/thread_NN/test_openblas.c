#include <stdio.h>
#include <cblas.h>
#include <sys/time.h>
#include <stdlib.h>
#include <omp.h>


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
  int i,j;

  for ( i=0; i<m; i++ )
    for ( j=0; j<n; j++ )
    {
		a[i*n+j]= 2.0 * (float)drand48( ) - 1.0 + 0.000001 * (i+j);
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


int main()
{

	openblas_set_num_threads(num);
	int i,j,k;
	int loop = 5;
	long M, N, K;
	float *A,*B,*C;
	double start, cost;
	double gflops;
	long lda,ldb,ldc;
	int flag =0 , pc;


	FILE *fp;
	if( (fp=fopen("openblas_thread_NT_M256.txt","w")) == NULL )
	{
		puts("Fail to open file!");
		exit(0);
	}


	for (j =0 ; j < 40; j++)
	{
			
			M = 256;
			N = 2048 + j * 256 ;
			K = 5000;

			lda = K;
			ldb = K;
			ldc = N;
			double ops = (double) M *N *K * 1.0e-09 * 2;

			fprintf(fp, "%d %d %d", M, N, K);
			for(pc =0; pc < 5; pc++)
			{	

				A = ( float * ) malloc( K*M* sizeof( float ) );  
				B = ( float * ) malloc( K* N * sizeof( float ) );
				C = ( float * ) malloc( M* N * sizeof( float ) );

				random_matrix(M,K,A);
				random_matrix(K,N,B);


				for( i =0 ;i< 2; i++)
					cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, M, N, K, 1.0, A, lda, 
						B, ldb, 0.0, C, ldc);

				start = dclock();
			 	for(i= 0; i<loop ;i++)
			  {

			   	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, M, N, K, 1.0, A, lda, 
			   		B, ldb, 0.0, C, ldc);
			  }
			  cost=(dclock()-start)/loop;

			  printf("OpenBLAS:  M= %d N=%d K=%d flops = %lf effic= %.3lf %\n\n", 
			    	M, N, K, ops/cost, ops/cost/17.6 * 100/num);
			  fprintf(fp, " %lf", ops/cost);

		    free(A);
		    free(B);
		    free(C);
			}
			fprintf(fp, "\n");
	}

  fclose(fp);
  return 0;

}
