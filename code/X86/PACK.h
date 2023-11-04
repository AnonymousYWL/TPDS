void NPACK(float* A, float* Ac, long M, long K, long LK)
{
	long ii, kk;
	int index = 0;
	
	for(kk = 0; kk < K; kk++)
	{
		for(ii = 0; ii < M; ii++)
		{
			Ac[index++] = A[ii * LK + kk];
		}
	}

}
