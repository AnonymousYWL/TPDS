#include<stdio.h>
#include<sys/time.h>
#include <stdlib.h>
#include <cblas.h>
#include <omp.h>

void SGEMM_NT_MP(float *C, float *A, float *B, long	M, long N, long K, 
			long LN, long LK, float *SB, long k_tag)
{
	asm volatile(
		".macro PACK_KERNEL5x4_BEGIN_K             	 \n"
		"										 	 \n"

		"	ldr		q0, [x11], #16					 \n"
		"	ldr		q1, [x12], #16				     \n"
		"	ldr		q5, [x16], #16					 \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"
		"	prfm	PLDL1KEEP, [x12, #64] 			 \n"
		"   prfm    PLDL1KEEP, [x13, #64]       	 \n"
		"	prfm	PLDL1KEEP, [x14, #64] 			 \n"
		"	prfm	PLDL1KEEP, [x15, #64]			 \n"

		"	prfm 	PLDL1KEEP, [x17, #128]			 \n"

		"	fmul	v12.4s, v0.4s, v5.4s			 \n"
		"	ldr		q2, [x13], #16					 \n"
		"	fmul	v13.4s, v1.4s, v5.4s			 \n"

		"	ldr		q3, [x14], #16					 \n"

		"	fmul	v14.4s, v2.4s, v5.4s		 	 \n"
		"	ldr		q4, [x15], #16					 \n"
		"	fmul	v15.4s, v3.4s, v5.4s			 \n"

		"	ldr		q6, [x17], #16					 \n"
		"	fmul	v16.4s, v4.4s, v5.4s			 \n"
		"	ldr		q7, [x18], #16					 \n"
		"	fmul	v17.4s, v0.4s, v6.4s			 \n"

		"	ldr		q8, [x19], #16					 \n"
		"	ldr		q9, [x11], #16					 \n"
		"	st4		{v5.s, v6.s, v7.s, v8.s}[0], [x24]		\n"
		"	add		x24, x24, x8, lsl #2			 \n"

		"	fmul	v18.4s, v1.4s, v6.4s			 \n"
		"	fmul	v19.4s, v2.4s, v6.4s			 \n"
		"	fmul	v20.4s, v3.4s, v6.4s			 \n"
		"	fmul	v21.4s, v4.4s, v6.4s			 \n"

		"	ldr		q10, [x12], #16					 \n"
		"	st4		{v5.s, v6.s, v7.s, v8.s}[1], [x24]		\n"
		"	add		x24, x24, x8, lsl #2			 \n"

		"	fmul	v22.4s, v0.4s, v7.4s			 \n"
		"	fmul	v23.4s, v1.4s, v7.4s			 \n"
		"	fmul	v24.4s, v2.4s, v7.4s			 \n"
		"	fmul	v25.4s, v3.4s, v7.4s			 \n"
		"	fmul	v26.4s, v4.4s, v7.4s			 \n"

		"	ldr		q11, [x13], #16					 \n"
		"	st4		{v5.s, v6.s, v7.s, v8.s}[2], [x24]		\n"
		"	add		x24, x24, x8, lsl #2			 \n"

		"	fmul	v27.4s, v0.4s, v8.4s			 \n"
		"	ldr		q0, [x14], #16					 \n"
		"	fmul	v28.4s, v1.4s, v8.4s			 \n"
		"	ldr		q1, [x15], #16					 \n"

		"	st4		{v5.s, v6.s, v7.s, v8.s}[3], [x24]		\n"
		"	add		x24, x24, x8, lsl #2			 \n"
		"	ldr		q5, [x16], #16					 \n"

		"	fmul	v29.4s, v2.4s, v8.4s			 \n"
		"	fmul	v30.4s, v3.4s, v8.4s			 \n"
		"	fmul	v31.4s, v4.4s, v8.4s			 \n"


		".endm									 	 \n"



		".macro PACK_KERNEL5x4_K0                    \n"

		"	prfm 	PLDL1KEEP, [x16, #128]			 \n"

		"	ldr		q6, [x17], #16					 \n"

		"	fmla	v12.4s, v0.4s, v5.4s			 \n"
		"	fmla	v13.4s, v1.4s, v5.4s			 \n"

		"	prfm 	PLDL1KEEP, [x17, #128]			 \n"

		"	ldr		q7, [x18], #16					 \n"

		"	prfm 	PLDL1KEEP, [x11, #64]			 \n"

		"	fmla	v14.4s, v2.4s, v5.4s			 \n"
		"	fmla	v15.4s, v3.4s, v5.4s			 \n"
		"	fmla	v16.4s, v4.4s, v5.4s			 \n"

		"	prfm 	PLDL1KEEP, [x12, #64]			 \n"

		"	ldr		q8, [x19], #16					 \n"
		"	st4		{v5.s, v6.s, v7.s, v8.s}[0], [x24]		\n"
		"	add		x24, x24, x8, lsl #2			 \n"

		"	fmla	v17.4s, v0.4s, v6.4s			 \n"
		"	fmla	v18.4s, v1.4s, v6.4s		 	 \n"
		"	fmla	v19.4s, v2.4s, v6.4s			 \n"
		"	fmla	v20.4s, v3.4s, v6.4s			 \n"
		"	fmla	v21.4s, v4.4s, v6.4s			 \n"

		"	ldr		q9, [x11], #16					 \n"
		"	st4		{v5.s, v6.s, v7.s, v8.s}[1], [x24]		\n"
		"	add		x24, x24, x8, lsl #2			 \n"

		"	fmla	v22.4s, v0.4s, v7.4s			 \n"
		"	fmla	v23.4s, v1.4s, v7.4s		 	 \n"

		"	ldr		q10, [x12], #16					 \n"
		"	st4		{v5.s, v6.s, v7.s, v8.s}[2], [x24]		\n"
		"	add		x24, x24, x8, lsl #2			 \n"

		"	fmla	v24.4s, v2.4s, v7.4s			 \n"
		"	fmla	v25.4s, v3.4s, v7.4s			 \n"
		"	fmla	v26.4s, v4.4s, v7.4s			 \n"

		"	ldr		q11, [x13], #16					 \n"
		"	st4		{v5.s, v6.s, v7.s, v8.s}[3], [x24]		\n"
		"	add		x24, x24, x8, lsl #2			 \n"

		"	fmla	v27.4s, v0.4s, v8.4s			 \n"
		"	ldr		q5, [x16], #16					 \n"
		"	ldr		q0, [x14], #16					 \n"
		"	fmla	v28.4s, v1.4s, v8.4s		 	 \n"
		"	ldr		q1, [x15], #16					 \n"

		"	fmla	v29.4s, v2.4s, v8.4s			 \n"
		"	fmla	v30.4s, v3.4s, v8.4s			 \n"
		"	fmla	v31.4s, v4.4s, v8.4s			 \n"

		".endm   									 \n"


		".macro PACK_KERNEL5x4_K1                    \n"

		"	prfm 	PLDL1KEEP, [x18, #128]			 \n"

		"	ldr		q6, [x17], #16					 \n"
		"	fmla	v12.4s, v9.4s, v5.4s 			 \n"
		"	fmla	v13.4s, v10.4s, v5.4s		  	 \n"

		"	prfm  	PLDL1KEEP, [x19, #128]			 \n"
		"	ldr		q7, [x18], #16					 \n"
		"	fmla	v14.4s, v11.4s, v5.4s		 	 \n"
		"	fmla	v15.4s, v0.4s, v5.4s			 \n"
		"	fmla	v16.4s, v1.4s, v5.4s			 \n"

		"	prfm 	PLDL1KEEP, [x13, #64]			 \n"
		"	ldr		q8, [x19], #16					 \n"
		"	st4		{v5.s, v6.s, v7.s, v8.s}[0], [x24]		\n"
		"	add		x24, x24, x8, lsl #2			 \n"

		"	fmla	v17.4s, v9.4s, v6.4s 			 \n"
		"	fmla	v18.4s, v10.4s, v6.4s		  	 \n"

		"	ldr		q2, [x13], #16					 \n"
		"	st4		{v5.s, v6.s, v7.s, v8.s}[1], [x24]		\n"
		"	add		x24, x24, x8, lsl #2			 \n"

		"	prfm  	PLDL1KEEP, [x14, #64]			 \n"
		"	fmla	v19.4s, v11.4s, v6.4s		 	 \n"
		"	fmla	v20.4s, v0.4s, v6.4s			 \n"
		"	fmla	v21.4s, v1.4s, v6.4s			 \n"

		"	prfm  	PLDL1KEEP, [x15, #64]			 \n"
		"	ldr		q3, [x14], #16					 \n"

		"	fmla	v25.4s, v0.4s, v7.4s			 \n"
		"	fmla	v26.4s, v1.4s, v7.4s			 \n"

		"	st4		{v5.s, v6.s, v7.s, v8.s}[2], [x24]		\n"
		"	add		x24, x24, x8, lsl #2			 \n"

		"	fmla	v30.4s, v0.4s, v8.4s			 \n"
		"	ldr		q0, [x11], #16					 \n"
		"	fmla	v31.4s, v1.4s, v8.4s			 \n"
		"	ldr		q1, [x12], #16					 \n"

		"	fmla	v22.4s, v9.4s, v7.4s		  	 \n"

		"	st4		{v5.s, v6.s, v7.s, v8.s}[3], [x24]		\n"
		"	add		x24, x24, x8, lsl #2			 \n"
		"	ldr		q5, [x16], #16					 \n"

		"	fmla	v23.4s, v10.4s, v7.4s			 \n"
		"	fmla	v24.4s, v11.4s, v7.4s			 \n"

		"	ldr		q4, [x15], #16					 \n"

		"	fmla	v27.4s, v9.4s, v8.4s			 \n"
		"	fmla	v28.4s, v10.4s, v8.4s			 \n"
		"	fmla	v29.4s, v11.4s, v8.4s			 \n"

		".endm									 	 \n"


		".macro PACK_KERNEL5x4_END_K                 \n"

		"	ldr		q6, [x17], #16					 \n"
		"	fmla	v12.4s, v9.4s, v5.4s 			 \n"
		"	fmla	v13.4s, v10.4s, v5.4s		  	 \n"

		"	ldr		q7, [x18], #16					 \n"
		"	fmla	v14.4s, v11.4s, v5.4s		 	 \n"
		"	fmla	v15.4s, v0.4s, v5.4s			 \n"
		"	fmla	v16.4s, v1.4s, v5.4s			 \n"

		"	ldr		q8, [x19], #16					 \n"
		"	st4		{v5.s, v6.s, v7.s, v8.s}[0], [x24]		\n"
		"	add		x24, x24, x8, lsl #2			 \n"

		"	fmla	v17.4s, v9.4s, v6.4s 			 \n"
		"	faddp	v12.4s, v12.4s, v17.4s			 \n"
		"	fmla	v18.4s, v10.4s, v6.4s		  	 \n"
		"	faddp	v13.4s, v13.4s, v18.4s			 \n"

		"	st4		{v5.s, v6.s, v7.s, v8.s}[1], [x24]		\n"
		"	add		x24, x24, x8, lsl #2			 \n"

		"	fmla	v19.4s, v11.4s, v6.4s		 	 \n"
		"	faddp	v14.4s, v14.4s, v19.4s			 \n"
		"	fmla	v20.4s, v0.4s, v6.4s			 \n"
		"	faddp	v15.4s, v15.4s, v20.4s			 \n"
		"	fmla	v21.4s, v1.4s, v6.4s			 \n"
		"	faddp	v16.4s, v16.4s, v21.4s			 \n"

		"	fmla	v25.4s, v0.4s, v7.4s			 \n"
		"	fmla	v26.4s, v1.4s, v7.4s			 \n"

		"	st4		{v5.s, v6.s, v7.s, v8.s}[2], [x24]		\n"
		"	add		x24, x24, x8, lsl #2			 \n"

		"	fmla	v30.4s, v0.4s, v8.4s			 \n"
		"	faddp	v25.4s, v25.4s, v30.4s			 \n"
		"	fmla	v31.4s, v1.4s, v8.4s			 \n"
		"	faddp	v26.4s, v26.4s, v31.4s			 \n"

		"	fmla	v22.4s, v9.4s, v7.4s		  	 \n"
		"	st4		{v5.s, v6.s, v7.s, v8.s}[3], [x24]		\n"
		"	add		x24, x24, x8, lsl #2			 \n"
		"	fmla	v23.4s, v10.4s, v7.4s			 \n"
		"	fmla	v24.4s, v11.4s, v7.4s			 \n"

		"	faddp	v15.4s, v15.4s, v25.4s			 \n"
		"	faddp 	v16.4s, v16.4s, v26.4s			 \n"

		"	fmla	v27.4s, v9.4s, v8.4s			 \n"
		"	faddp 	v22.4s, v22.4s, v27.4s			 \n"
		"	fmla	v28.4s, v10.4s, v8.4s			 \n"
		"	faddp	v23.4s, v23.4s, v28.4s			 \n"
		"	fmla	v29.4s, v11.4s, v8.4s			 \n"
		"	faddp	v24.4s, v24.4s, v29.4s			 \n"

		"	faddp	v12.4s, v12.4s, v22.4s			 \n"
		"	faddp	v13.4s, v13.4s, v23.4s		 	 \n"
		"	faddp	v14.4s, v14.4s, v24.4s			 \n"

		".endm 										 \n"


		".macro	PACKB_ADD_C 						 \n"

		"	ldr		q0, [x25]						 \n"
		"	ldr		q1, [x26]						 \n"

		"	fadd 	v12.4s, v12.4s, v0.4s			 \n"
		"	ldr		q2, [x27]						 \n"
		"	fadd 	v13.4s, v13.4s, v1.4s			 \n"
		"	ldr		q3, [x28]						 \n"
		"	fadd 	v14.4s, v14.4s, v2.4s			 \n"
		"	ldr		q4, [x29]						 \n"
		"	fadd 	v15.4s, v15.4s, v3.4s			 \n"
		"	fadd 	v16.4s, v16.4s, v4.4s			 \n"


		".endm 									 	 \n"


		".macro SAVE5x4							 	 \n"

		"	subs	x7, x7, #1					 	 \n"

		"	str		q12, [x25], #16					 \n"
		"	str		q13, [x26], #16					 \n"
		"	str		q14, [x27], #16		 			 \n"
		"	str		q15, [x28], #16		 			 \n"
		"	str		q16, [x29], #16					 \n"

		".endm 									 	 \n"


		".macro ADD_C								 \n"

		"	prfm	PLDL1KEEP, [x25, #64]			 \n"
		"	prfm	PLDL1KEEP, [x26, #64]			 \n"
		"	prfm	PLDL1KEEP, [x27, #64]			 \n"
		"	prfm	PLDL1KEEP, [x28, #64]			 \n"
		"	prfm	PLDL1KEEP, [x29, #64]			 \n"

		"	ldp		q0, q1, [x25]					 \n"

		"	fadd	v12.4s, v12.4s, v0.4s			 \n"
		"	ldp		q2, q3, [x25, #32]				 \n"
		"	fadd	v13.4s, v13.4s, v1.4s			 \n"

		"	fadd	v22.4s, v2.4s, v22.4s			 \n"
		"	ldp		q4, q5, [x26]					 \n"
		"	fadd	v23.4s, v3.4s, v23.4s		 	 \n"

		"	fadd	v14.4s, v4.4s, v14.4s			 \n"
		"	ldp		q6, q7, [x26, #32]				 \n"
		"	fadd	v15.4s, v5.4s, v15.4s			 \n"

		"	prfm	PLDL1KEEP, [x27, #64]			 \n"
		"	prfm	PLDL1KEEP, [x28, #64]			 \n"
		"	prfm	PLDL1KEEP, [x29, #64]			 \n"

		"	fadd	v24.4s, v6.4s, v24.4s			 \n"
		"	ldp		q8, q9, [x27]					 \n"
		"	fadd 	v25.4s, v7.4s, v25.4s			 \n"

		"	fadd	v16.4s, v8.4s, v16.4s			 \n"
		"	ldp		q10, q11, [x27, #32]			 \n"
		"	fadd	v17.4s, v9.4s, v17.4s			 \n"

		"	fadd	v26.4s, v10.4s, v26.4s			 \n"
		"	ldp		q0, q1, [x28]				  	 \n"
		"	fadd	v27.4s, v11.4s, v27.4s			 \n"


		"	fadd	v18.4s, v0.4s, v18.4s			 \n"
		"	ldp		q2, q3, [x28, #32]				 \n"
		"	fadd	v19.4s, v1.4s, v19.4s			 \n"

		"	fadd	v28.4s, v2.4s, v28.4s			 \n"
		"	ldp		q4, q5, [x29]					 \n"
		"	fadd	v29.4s, v3.4s, v29.4s			 \n"

		"	fadd	v20.4s, v4.4s, v20.4s			 \n"
		"	ldp		q6, q7, [x29, #32]				 \n"
		"	fadd	v21.4s, v5.4s, v21.4s			 \n"

		"	fadd	v30.4s, v30.4s, v6.4s			 \n"
		"	fadd	v31.4s, v31.4s, v7.4s		     \n"

		".endm 										 \n"


		".macro SAVE5x16							 \n"


		"	subs	x21, x21, #1					 \n"

		"	stp		q12, q13, [x25]			 		 \n"
		"	stp		q14, q15, [x26]			 	     \n"
		"	stp		q16, q17, [x27]					 \n"
		"	stp		q18, q19, [x28]					 \n"
		"	stp		q20, q21, [x29]					 \n"

//		"	add 	x10, x10, x9					 \n"

		"	add 	x10, x10, x6, lsl #4			 \n"
		"	add		x10, x10, x6, lsl #2 			 \n"

		"	stp		q22, q23, [x25, #32]			 \n"
		"	add		x25, x29, x9, lsl #2					 \n"
		"	stp		q24, q25, [x26, #32]			 \n"
		"	add		x26, x29, x9, lsl #3			 \n"
		"	stp		q26, q27, [x27, #32]			 \n"
		"	add		x27, x25, x9, lsl #3 			 \n"
		"	stp		q28, q29, [x28, #32]			 \n"
		"	add		x28, x26, x9, lsl #3 			 \n"
		"	stp		q30, q31, [x29, #32]			 \n"
		"	add		x29, x27, x9, lsl #3			 \n"

		".endm 									 	 \n"


		".macro KERNEL5x16_BEGIN_K             	 	 \n"
		"										 	 \n"

		"	ldr		q0, [x11], #16					 \n"
		"	ldr		q1, [x12], #16					 \n"
		"	ldp		q8, q9, [x24], #32			     \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"
		"	prfm	PLDL1KEEP, [x12, #64] 			 \n"
		"   prfm    PLDL1KEEP, [x13, #64]       	 \n"
		"	prfm	PLDL1KEEP, [x14, #64] 			 \n"
		"	prfm	PLDL1KEEP, [x15, #64]			 \n"

		"	fmul	v12.4s, v8.4s, v0.s[0]	         \n"
		"	fmul	v13.4s, v9.4s, v0.s[0]	         \n"

		"	ldr		q2, [x13], #16					 \n"

		"	fmul	v14.4s, v8.4s, v1.s[0]	         \n"
		"	fmul	v15.4s, v9.4s, v1.s[0]	         \n"

		"	ldr		q3, [x14], #16					 \n"

		"	fmul	v16.4s, v8.4s, v2.s[0]	         \n"
		"	fmul	v17.4s, v9.4s, v2.s[0]	         \n"

		"	prfm	PLDL1KEEP, [x24, #128]			 \n"

		"	ldr		q4, [x15], #16				 	 \n"

		"	fmul	v18.4s, v8.4s, v3.s[0]	         \n"
		"	fmul	v19.4s, v9.4s, v3.s[0]	         \n"

		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmul	v20.4s, v8.4s, v4.s[0]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmul	v21.4s, v9.4s, v4.s[0]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmul	v22.4s, v10.4s, v0.s[0]			 \n"
		"	fmul	v23.4s, v11.4s, v0.s[0]			 \n"

		"	fmul	v24.4s, v10.4s, v1.s[0]	         \n"
		"	fmul	v25.4s, v11.4s, v1.s[0]	         \n"

		"	fmul	v26.4s, v10.4s, v2.s[0]	         \n"
		"	fmul	v27.4s, v11.4s, v2.s[0]	         \n"

		"	ldr		q5, [x11], #16					 \n"

		"	fmul	v28.4s, v10.4s, v3.s[0]	         \n"
		"	fmul	v29.4s, v11.4s, v3.s[0]	         \n"

		"	fmul	v30.4s, v10.4s, v4.s[0]	         \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmul	v31.4s, v11.4s, v4.s[0]	         \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm									 	 \n"


		".macro KERNEL5x16_K0                   	 \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"

		"	fmla	v12.4s, v8.4s, v0.s[0]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[0]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v14.4s, v8.4s, v1.s[0]			 \n"
		"	fmla 	v15.4s, v9.4s, v1.s[0]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[0]			 \n"
		"	fmla 	v17.4s, v9.4s, v2.s[0]			 \n"

		"	fmla	v18.4s, v8.4s, v3.s[0]			 \n"
		"	fmla 	v19.4s, v9.4s, v3.s[0]			 \n"

		"	fmla	v20.4s, v8.4s, v4.s[0]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla	v21.4s, v9.4s, v4.s[0]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v0.s[0]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[0]			 \n"

		"	fmla	v24.4s, v10.4s, v1.s[0]			 \n"
		"	fmla	v25.4s, v11.4s, v1.s[0]			 \n"

		"	fmla	v26.4s, v10.4s, v2.s[0]			 \n"
		"	fmla	v27.4s, v11.4s, v2.s[0]			 \n"

		"	ldr		q5, [x11], #16					 \n"  // 

		"	fmla	v28.4s, v10.4s, v3.s[0]			 \n"
		"	fmla	v29.4s, v11.4s, v3.s[0]			 \n"

		"	fmla	v30.4s, v10.4s, v4.s[0]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v31.4s, v11.4s, v4.s[0]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm   									 \n"


		".macro KERNEL5x16_K1        	             \n"

		"   prfm    PLDL1KEEP, [x12, #64]       	 \n"
		"	fmla	v12.4s, v8.4s, v0.s[1]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[1]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v14.4s, v8.4s, v1.s[1]			 \n"
		"	fmla	v15.4s, v9.4s, v1.s[1]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[1]			 \n"
		"	fmla	v17.4s, v9.4s, v2.s[1]			 \n"

		"	fmla	v18.4s, v8.4s, v3.s[1]			 \n"
		"	fmla	v19.4s, v9.4s, v3.s[1]			 \n"

		"	fmla	v20.4s, v8.4s, v4.s[1]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla	v21.4s, v9.4s, v4.s[1]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v0.s[1]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[1]			 \n"

		"	fmla	v24.4s, v10.4s, v1.s[1]			 \n"
		"	fmla	v25.4s, v11.4s, v1.s[1]			 \n"

		"	fmla	v26.4s, v10.4s, v2.s[1]			 \n"
		"	fmla	v27.4s, v11.4s, v2.s[1]			 \n"

		"	ldr		q6, [x12], #16					 \n"

		"	fmla	v28.4s, v10.4s, v3.s[1]			 \n"
		"	fmla	v29.4s, v11.4s, v3.s[1]			 \n"

		"	fmla	v30.4s, v10.4s, v4.s[1]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v31.4s, v11.4s, v4.s[1]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm									 	 \n"


		".macro KERNEL5x16_K2          		         \n"

		"   prfm    PLDL1KEEP, [x13, #64]       	 \n"

		"	fmla	v12.4s, v8.4s, v0.s[2]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[2]			 \n"

		"	fmla	v14.4s, v8.4s, v1.s[2]			 \n"
		"	fmla 	v15.4s, v9.4s, v1.s[2]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[2]			 \n"
		"	fmla 	v17.4s, v9.4s, v2.s[2]			 \n"

		"	fmla	v18.4s, v8.4s, v3.s[2]			 \n"
		"	fmla 	v19.4s, v9.4s, v3.s[2]			 \n"

		"	fmla	v20.4s, v8.4s, v4.s[2]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla	v21.4s, v9.4s, v4.s[2]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v0.s[2]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[2]			 \n"

		"	prfm	PLDL1KEEP, [x14, #64]			 \n"

		"	fmla	v24.4s, v10.4s, v1.s[2]			 \n"
		"	fmla	v25.4s, v11.4s, v1.s[2]			 \n"

		"	fmla	v26.4s, v10.4s, v2.s[2]			 \n"
		"	fmla	v27.4s, v11.4s, v2.s[2]			 \n"

		"	ldr		q7, [x13], #16					 \n"  // 

		"	fmla	v28.4s, v10.4s, v3.s[2]			 \n"
		"	fmla	v29.4s, v11.4s, v3.s[2]			 \n"

		"	fmla	v30.4s, v10.4s, v4.s[2]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v31.4s, v11.4s, v4.s[2]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm									 	 \n"


		".macro KERNEL5x16_K3   	                 \n"

		"   prfm    PLDL1KEEP, [x15, #64]       	 \n"
		"	fmla	v12.4s, v8.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[3]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v14.4s, v8.4s, v1.s[3]			 \n"
		"	fmla	v15.4s, v9.4s, v1.s[3]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[3]			 \n"
		"	fmla	v17.4s, v9.4s, v2.s[3]			 \n"

		"	fmla	v18.4s, v8.4s, v3.s[3]			 \n"
		"	fmla	v19.4s, v9.4s, v3.s[3]			 \n"

		"	fmla	v20.4s, v8.4s, v4.s[3]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla	v21.4s, v9.4s, v4.s[3]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[3]			 \n"

		"	ldr		q0, [x14], #16					 \n"

		"	fmla	v24.4s, v10.4s, v1.s[3]			 \n"
		"	fmla	v25.4s, v11.4s, v1.s[3]			 \n"

		"	ldr		q1, [x15], #16					 \n"

		"	fmla	v26.4s, v10.4s, v2.s[3]			 \n"
		"	fmla	v27.4s, v11.4s, v2.s[3]			 \n"

		"	fmla	v28.4s, v10.4s, v3.s[3]			 \n"
		"	fmla	v29.4s, v11.4s, v3.s[3]			 \n"

		"	fmla	v30.4s, v10.4s, v4.s[3]			 \n"
		"	ldr		q10, [x24], #16				 	 \n"
		"	fmla	v31.4s, v11.4s, v4.s[3]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm									 	 \n"


		".macro KERNEL5x16_K4    	                 \n"

		"	prfm	PLDL1KEEP, [x13, #64]			 \n"

		"	fmla	v12.4s, v8.4s, v5.s[0]			 \n"
		"	fmla	v13.4s, v9.4s, v5.s[0]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v14.4s, v8.4s, v6.s[0]			 \n"
		"	fmla 	v15.4s, v9.4s, v6.s[0]			 \n"

		"	fmla	v16.4s, v8.4s, v7.s[0]			 \n"
		"	fmla 	v17.4s, v9.4s, v7.s[0]			 \n"

		"	fmla	v18.4s, v8.4s, v0.s[0]			 \n"
		"	fmla 	v19.4s, v9.4s, v0.s[0]			 \n"

		"	fmla	v20.4s, v8.4s, v1.s[0]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla	v21.4s, v9.4s, v1.s[0]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v5.s[0]			 \n"
		"	fmla	v23.4s, v11.4s, v5.s[0]			 \n"

		"	fmla	v24.4s, v10.4s, v6.s[0]			 \n"
		"	fmla	v25.4s, v11.4s, v6.s[0]			 \n"

		"	fmla	v26.4s, v10.4s, v7.s[0]			 \n"
		"	fmla	v27.4s, v11.4s, v7.s[0]			 \n"

		"	ldr		q2, [x13], #16					 \n"  // 

		"	fmla	v28.4s, v10.4s, v0.s[0]			 \n"
		"	fmla	v29.4s, v11.4s, v0.s[0]			 \n"

		"	fmla	v30.4s, v10.4s, v1.s[0]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v31.4s, v11.4s, v1.s[0]			 \n"
		"	ldr		q11, [x24], #16					 \n"


		".endm 										 \n"


		".macro KERNEL5x16_K5         	             \n"

		"   prfm    PLDL1KEEP, [x14, #64]       	 \n"
		"	fmla	v12.4s, v8.4s, v5.s[1]			 \n"
		"	fmla	v13.4s, v9.4s, v5.s[1]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v14.4s, v8.4s, v6.s[1]			 \n"
		"	fmla	v15.4s, v9.4s, v6.s[1]			 \n"

		"	fmla	v16.4s, v8.4s, v7.s[1]			 \n"
		"	fmla	v17.4s, v9.4s, v7.s[1]			 \n"

		"	fmla	v18.4s, v8.4s, v0.s[1]			 \n"
		"	fmla	v19.4s, v9.4s, v0.s[1]			 \n"

		"	fmla	v20.4s, v8.4s, v1.s[1]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla	v21.4s, v9.4s, v1.s[1]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v5.s[1]			 \n"
		"	fmla	v23.4s, v11.4s, v5.s[1]			 \n"

		"	fmla	v24.4s, v10.4s, v6.s[1]			 \n"
		"	fmla	v25.4s, v11.4s, v6.s[1]			 \n"

		"	fmla	v26.4s, v10.4s, v7.s[1]			 \n"
		"	fmla	v27.4s, v11.4s, v7.s[1]			 \n"

		"	ldr		q3, [x14], #16					 \n"

		"	fmla	v28.4s, v10.4s, v0.s[1]			 \n"
		"	fmla	v29.4s, v11.4s, v0.s[1]			 \n"

		"	fmla	v30.4s, v10.4s, v1.s[1]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v31.4s, v11.4s, v1.s[1]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm 										 \n"


		".macro KERNEL5x16_K6 	                     \n"

		"	prfm	PLDL1KEEP, [x15, #64]			 \n"

		"	fmla	v12.4s, v8.4s, v5.s[2]			 \n"
		"	fmla	v13.4s, v9.4s, v5.s[2]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v14.4s, v8.4s, v6.s[2]			 \n"
		"	fmla 	v15.4s, v9.4s, v6.s[2]			 \n"

		"	fmla	v16.4s, v8.4s, v7.s[2]			 \n"
		"	fmla 	v17.4s, v9.4s, v7.s[2]			 \n"

		"	fmla	v18.4s, v8.4s, v0.s[2]			 \n"
		"	fmla 	v19.4s, v9.4s, v0.s[2]			 \n"

		"	fmla	v20.4s, v8.4s, v1.s[2]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla	v21.4s, v9.4s, v1.s[2]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v5.s[2]			 \n"
		"	fmla	v23.4s, v11.4s, v5.s[2]			 \n"

		"	fmla	v24.4s, v10.4s, v6.s[2]			 \n"
		"	fmla	v25.4s, v11.4s, v6.s[2]			 \n"

		"	prfm	PLDL1KEEP, [x11, #64]			 \n"

		"	fmla	v26.4s, v10.4s, v7.s[2]			 \n"
		"	fmla	v27.4s, v11.4s, v7.s[2]			 \n"

		"	ldr		q4, [x15], #16					 \n"  // 

		"	fmla	v28.4s, v10.4s, v0.s[2]			 \n"
		"	fmla	v29.4s, v11.4s, v0.s[2]			 \n"

		"	fmla	v30.4s, v10.4s, v1.s[2]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v31.4s, v11.4s, v1.s[2]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm 										 \n"


		".macro KERNEL5x16_K7      		             \n"

		"   prfm    PLDL1KEEP, [x12, #64]       	 \n"
		"	fmla	v12.4s, v8.4s, v5.s[3]			 \n"
		"	fmla	v13.4s, v9.4s, v5.s[3]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v14.4s, v8.4s, v6.s[3]			 \n"
		"	fmla	v15.4s, v9.4s, v6.s[3]			 \n"

		"	fmla	v16.4s, v8.4s, v7.s[3]			 \n"
		"	fmla	v17.4s, v9.4s, v7.s[3]			 \n"

		"	fmla	v18.4s, v8.4s, v0.s[3]			 \n"
		"	fmla	v19.4s, v9.4s, v0.s[3]			 \n"

		"	fmla	v20.4s, v8.4s, v1.s[3]			 \n"
		"	ldr		q8, [x24], #16			     	 \n"
		"	fmla	v21.4s, v9.4s, v1.s[3]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v28.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v29.4s, v11.4s, v0.s[3]			 \n"

		"	ldr		q0, [x11], #16					 \n"

		"	fmla	v30.4s, v10.4s, v1.s[3]			 \n"
		"	fmla	v31.4s, v11.4s, v1.s[3]			 \n"

		"	ldr		q1, [x12], #16					 \n"

		"	fmla	v22.4s, v10.4s, v5.s[3]			 \n"
		"	fmla	v23.4s, v11.4s, v5.s[3]			 \n"

		"	fmla	v24.4s, v10.4s, v6.s[3]			 \n"
		"	fmla	v25.4s, v11.4s, v6.s[3]			 \n"

		"	fmla	v26.4s, v10.4s, v7.s[3]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v27.4s, v11.4s, v7.s[3]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm 										 \n"


		".macro KERNEL5x16_END_K                	 \n"

		"	fmla	v12.4s, v8.4s, v5.s[3]			 \n"
		"	fmla	v13.4s, v9.4s, v5.s[3]			 \n"

		"	fmla	v14.4s, v8.4s, v6.s[3]			 \n"
		"	fmla	v15.4s, v9.4s, v6.s[3]			 \n"

		"	fmla	v16.4s, v8.4s, v7.s[3]			 \n"
		"	fmla	v17.4s, v9.4s, v7.s[3]			 \n"

		"	fmla	v18.4s, v8.4s, v0.s[3]			 \n"
		"	fmla	v19.4s, v9.4s, v0.s[3]			 \n"

		"	fmla	v20.4s, v8.4s, v1.s[3]			 \n"
		"	fmla	v21.4s, v9.4s, v1.s[3]			 \n"

		"	fmla	v28.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v29.4s, v11.4s, v0.s[3]			 \n"

		"	fmla	v30.4s, v10.4s, v1.s[3]			 \n"
		"	fmla	v31.4s, v11.4s, v1.s[3]			 \n"

		"	fmla	v22.4s, v10.4s, v5.s[3]			 \n"
		"	fmla	v23.4s, v11.4s, v5.s[3]			 \n"

		"	fmla	v24.4s, v10.4s, v6.s[3]			 \n"
		"	fmla	v25.4s, v11.4s, v6.s[3]			 \n"

		"	fmla	v26.4s, v10.4s, v7.s[3]			 \n"
		"	fmla	v27.4s, v11.4s, v7.s[3]			 \n"

		".endm 										 \n"



		".macro	KERNEL4x16_BEGIN_K					 \n"

		"										 	 \n"
		"	ldr		q0, [x11], #16					 \n"
		"	ldr		q1, [x12], #16					 \n"
		"	ldp		q8, q9, [x24], #32			     \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"
		"	prfm	PLDL1KEEP, [x12, #64] 			 \n"
		"   prfm    PLDL1KEEP, [x13, #64]       	 \n"
		"	prfm	PLDL1KEEP, [x14, #64] 			 \n"

		"	fmul	v12.4s, v8.4s, v0.s[0]	         \n"
		"	fmul	v13.4s, v9.4s, v0.s[0]	         \n"

		"	ldr		q2, [x13], #16					 \n"

		"	fmul	v14.4s, v8.4s, v1.s[0]	         \n"
		"	fmul	v15.4s, v9.4s, v1.s[0]	         \n"

		"	ldr		q3, [x14], #16					 \n"

		"	fmul	v16.4s, v8.4s, v2.s[0]	         \n"
		"	fmul	v17.4s, v9.4s, v2.s[0]	         \n"

		"	prfm	PLDL1KEEP, [x24, #128]			 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmul	v18.4s, v8.4s, v3.s[0]	         \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmul	v19.4s, v9.4s, v3.s[0]	         \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmul	v22.4s, v10.4s, v0.s[0]			 \n"
		"	fmul	v23.4s, v11.4s, v0.s[0]			 \n"

		"	fmul	v24.4s, v10.4s, v1.s[0]	         \n"
		"	fmul	v25.4s, v11.4s, v1.s[0]	         \n"

		"	fmul	v26.4s, v10.4s, v2.s[0]	         \n"
		"	fmul	v27.4s, v11.4s, v2.s[0]	         \n"

//		"	ldr		q5, [x11], #16					 \n"

		"	fmul	v28.4s, v10.4s, v3.s[0]	         \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmul	v29.4s, v11.4s, v3.s[0]	         \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm 										 \n"


		".macro KERNEL4x16_K0                   	 \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"

		"	fmla	v12.4s, v8.4s, v0.s[0]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[0]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v14.4s, v8.4s, v1.s[0]			 \n"
		"	fmla 	v15.4s, v9.4s, v1.s[0]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[0]			 \n"
		"	fmla 	v17.4s, v9.4s, v2.s[0]			 \n"

		"	fmla	v18.4s, v8.4s, v3.s[0]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla 	v19.4s, v9.4s, v3.s[0]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v0.s[0]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[0]			 \n"

		"	fmla	v24.4s, v10.4s, v1.s[0]			 \n"
		"	fmla	v25.4s, v11.4s, v1.s[0]			 \n"

		"	fmla	v26.4s, v10.4s, v2.s[0]			 \n"
		"	fmla	v27.4s, v11.4s, v2.s[0]			 \n"

//		"	ldr		q5, [x11], #16					 \n"  // 

		"	fmla	v28.4s, v10.4s, v3.s[0]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v29.4s, v11.4s, v3.s[0]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm   									 \n"


		".macro KERNEL4x16_K1        	             \n"

		"   prfm    PLDL1KEEP, [x12, #64]       	 \n"
		"	fmla	v12.4s, v8.4s, v0.s[1]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[1]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v14.4s, v8.4s, v1.s[1]			 \n"
		"	fmla	v15.4s, v9.4s, v1.s[1]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[1]			 \n"
		"	fmla	v17.4s, v9.4s, v2.s[1]			 \n"

		"	fmla	v18.4s, v8.4s, v3.s[1]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla	v19.4s, v9.4s, v3.s[1]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v0.s[1]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[1]			 \n"

		"	fmla	v24.4s, v10.4s, v1.s[1]			 \n"
		"	fmla	v25.4s, v11.4s, v1.s[1]			 \n"

		"	fmla	v26.4s, v10.4s, v2.s[1]			 \n"
		"	fmla	v27.4s, v11.4s, v2.s[1]			 \n"

//		"	ldr		q6, [x12], #16					 \n"

		"	fmla	v28.4s, v10.4s, v3.s[1]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v29.4s, v11.4s, v3.s[1]			 \n"
		"	ldr		q11, [x24], #16					 \n"


		".endm									 	 \n"


		".macro KERNEL4x16_K2          		         \n"

		"   prfm    PLDL1KEEP, [x13, #64]       	 \n"

		"	fmla	v12.4s, v8.4s, v0.s[2]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[2]			 \n"

		"	fmla	v14.4s, v8.4s, v1.s[2]			 \n"
		"	fmla 	v15.4s, v9.4s, v1.s[2]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[2]			 \n"
		"	fmla 	v17.4s, v9.4s, v2.s[2]			 \n"

		"	fmla	v18.4s, v8.4s, v3.s[2]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla 	v19.4s, v9.4s, v3.s[2]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v0.s[2]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[2]			 \n"

		"	prfm	PLDL1KEEP, [x14, #64]			 \n"

		"	fmla	v24.4s, v10.4s, v1.s[2]			 \n"
		"	fmla	v25.4s, v11.4s, v1.s[2]			 \n"

		"	fmla	v26.4s, v10.4s, v2.s[2]			 \n"
		"	fmla	v27.4s, v11.4s, v2.s[2]			 \n"

//		"	ldr		q7, [x13], #16					 \n"  // 

		"	fmla	v28.4s, v10.4s, v3.s[2]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v29.4s, v11.4s, v3.s[2]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm									 	 \n"


		".macro KERNEL4x16_K3   	                 \n"

		"   prfm    PLDL1KEEP, [x14, #64]       	 \n"
		"	fmla	v12.4s, v8.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[3]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v14.4s, v8.4s, v1.s[3]			 \n"
		"	fmla	v15.4s, v9.4s, v1.s[3]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[3]			 \n"
		"	fmla	v17.4s, v9.4s, v2.s[3]			 \n"

		"	fmla	v18.4s, v8.4s, v3.s[3]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla	v19.4s, v9.4s, v3.s[3]			 \n"
		"	ldr		q9, [x24], #16					 \n"


		"	fmla	v22.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[3]			 \n"

		"	ldr		q0, [x11], #16					 \n"

		"	fmla	v24.4s, v10.4s, v1.s[3]			 \n"
		"	fmla	v25.4s, v11.4s, v1.s[3]			 \n"

		"	ldr		q1, [x12], #16					 \n"

		"	fmla	v26.4s, v10.4s, v2.s[3]			 \n"
		"	fmla	v27.4s, v11.4s, v2.s[3]			 \n"

		"	ldr		q2, [x13], #16					 \n"

		"	fmla	v28.4s, v10.4s, v3.s[3]			 \n"
		"	ldr		q10, [x24], #16				 	 \n"
		"	fmla	v29.4s, v11.4s, v3.s[3]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		"	ldr		q3, [x14], #16					 \n"

		".endm									 	 \n"


		".macro KERNEL4x16_END_K   	                 \n"

		"	fmla	v12.4s, v8.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[3]			 \n"

		"	fmla	v14.4s, v8.4s, v1.s[3]			 \n"
		"	fmla	v15.4s, v9.4s, v1.s[3]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[3]			 \n"
		"	fmla	v17.4s, v9.4s, v2.s[3]			 \n"

		"	fmla	v18.4s, v8.4s, v3.s[3]			 \n"
		"	fmla	v19.4s, v9.4s, v3.s[3]			 \n"

		"	fmla	v22.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[3]			 \n"

		"	fmla	v24.4s, v10.4s, v1.s[3]			 \n"
		"	fmla	v25.4s, v11.4s, v1.s[3]			 \n"

		"	fmla	v26.4s, v10.4s, v2.s[3]			 \n"
		"	fmla	v27.4s, v11.4s, v2.s[3]			 \n"

		"	fmla	v28.4s, v10.4s, v3.s[3]			 \n"
		"	fmla	v29.4s, v11.4s, v3.s[3]			 \n"

		".endm									 	 \n"


		".macro	M4_ADD_C 							 \n"

		"	prfm	PLDL1KEEP, [x25, #64]			 \n"
		"	prfm	PLDL1KEEP, [x26, #64]			 \n"
		"	prfm	PLDL1KEEP, [x27, #64]			 \n"
		"	prfm	PLDL1KEEP, [x28, #64]			 \n"

		"	ldp		q0, q1, [x25]					 \n"

		"	fadd	v12.4s, v12.4s, v0.4s			 \n"
		"	ldp		q2, q3, [x25, #32]				 \n"
		"	fadd	v13.4s, v13.4s, v1.4s			 \n"

		"	fadd	v22.4s, v2.4s, v22.4s			 \n"
		"	ldp		q4, q5, [x26]					 \n"
		"	fadd	v23.4s, v3.4s, v23.4s		 	 \n"

		"	fadd	v14.4s, v4.4s, v14.4s			 \n"
		"	ldp		q6, q7, [x26, #32]				 \n"
		"	fadd	v15.4s, v5.4s, v15.4s			 \n"

		"	prfm	PLDL1KEEP, [x27, #64]			 \n"
		"	prfm	PLDL1KEEP, [x28, #64]			 \n"

		"	fadd	v24.4s, v6.4s, v24.4s			 \n"
		"	ldp		q8, q9, [x27]					 \n"
		"	fadd 	v25.4s, v7.4s, v25.4s			 \n"

		"	fadd	v16.4s, v8.4s, v16.4s			 \n"
		"	ldp		q10, q11, [x27, #32]			 \n"
		"	fadd	v17.4s, v9.4s, v17.4s			 \n"

		"	fadd	v26.4s, v10.4s, v26.4s			 \n"
		"	ldp		q0, q1, [x28]				  	 \n"
		"	fadd	v27.4s, v11.4s, v27.4s			 \n"

		"	fadd	v18.4s, v0.4s, v18.4s			 \n"
		"	ldp		q2, q3, [x28, #32]				 \n"
		"	fadd	v19.4s, v1.4s, v19.4s			 \n"

		"	fadd	v28.4s, v2.4s, v28.4s			 \n"
		"	fadd	v29.4s, v3.4s, v29.4s			 \n"

		".endm 										 \n"


		".macro SAVE4x16							 \n"

		"	stp		q12, q13, [x25]			 		 \n"
		"	stp		q14, q15, [x26]			 	     \n"
		"	stp		q16, q17, [x27]					 \n"
		"	stp		q18, q19, [x28]					 \n"

		"	stp		q22, q23, [x25, #32]			 \n"
		"	stp		q24, q25, [x26, #32]			 \n"
		"	stp		q26, q27, [x27, #32]			 \n"
		"	stp		q28, q29, [x28, #32]			 \n"

		".endm 									 	 \n"


		".macro	KERNEL3x16_BEGIN_K					 \n"

		"										 	 \n"
		"	ldr		q0, [x11], #16					 \n"
		"	ldr		q1, [x12], #16					 \n"
		"	ldp		q8, q9, [x24], #32			     \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"
		"	prfm	PLDL1KEEP, [x12, #64] 			 \n"
		"   prfm    PLDL1KEEP, [x13, #64]       	 \n"

		"	fmul	v12.4s, v8.4s, v0.s[0]	         \n"
		"	fmul	v13.4s, v9.4s, v0.s[0]	         \n"

		"	ldr		q2, [x13], #16					 \n"

		"	fmul	v14.4s, v8.4s, v1.s[0]	         \n"
		"	fmul	v15.4s, v9.4s, v1.s[0]	         \n"

		"	prfm	PLDL1KEEP, [x24, #128]			 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmul	v16.4s, v8.4s, v2.s[0]	         \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmul	v17.4s, v9.4s, v2.s[0]	         \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmul	v22.4s, v10.4s, v0.s[0]			 \n"
		"	fmul	v23.4s, v11.4s, v0.s[0]			 \n"

		"	fmul	v24.4s, v10.4s, v1.s[0]	         \n"
		"	fmul	v25.4s, v11.4s, v1.s[0]	         \n"

		"	fmul	v26.4s, v10.4s, v2.s[0]	         \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmul	v27.4s, v11.4s, v2.s[0]	         \n"
		"	ldr		q11, [x24], #16					 \n"


		".endm 										 \n"


		".macro KERNEL3x16_K0                   	 \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"

		"	fmla	v12.4s, v8.4s, v0.s[0]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[0]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v14.4s, v8.4s, v1.s[0]			 \n"
		"	fmla 	v15.4s, v9.4s, v1.s[0]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[0]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla 	v17.4s, v9.4s, v2.s[0]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v0.s[0]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[0]			 \n"

		"	fmla	v24.4s, v10.4s, v1.s[0]			 \n"
		"	fmla	v25.4s, v11.4s, v1.s[0]			 \n"

		"	fmla	v26.4s, v10.4s, v2.s[0]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v27.4s, v11.4s, v2.s[0]			 \n"
		"	ldr		q11, [x24], #16					 \n"


		".endm   									 \n"


		".macro KERNEL3x16_K1        	             \n"

		"   prfm    PLDL1KEEP, [x12, #64]       	 \n"
		"	fmla	v12.4s, v8.4s, v0.s[1]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[1]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v14.4s, v8.4s, v1.s[1]			 \n"
		"	fmla	v15.4s, v9.4s, v1.s[1]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[1]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla	v17.4s, v9.4s, v2.s[1]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v0.s[1]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[1]			 \n"

		"	fmla	v24.4s, v10.4s, v1.s[1]			 \n"
		"	fmla	v25.4s, v11.4s, v1.s[1]			 \n"

		"	fmla	v26.4s, v10.4s, v2.s[1]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v27.4s, v11.4s, v2.s[1]			 \n"
		"	ldr		q11, [x24], #16					 \n"


		".endm									 	 \n"


		".macro KERNEL3x16_K2          		         \n"

		"   prfm    PLDL1KEEP, [x13, #64]       	 \n"

		"	fmla	v12.4s, v8.4s, v0.s[2]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[2]			 \n"

		"	fmla	v14.4s, v8.4s, v1.s[2]			 \n"
		"	fmla 	v15.4s, v9.4s, v1.s[2]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[2]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla 	v17.4s, v9.4s, v2.s[2]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v0.s[2]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[2]			 \n"

		"	fmla	v24.4s, v10.4s, v1.s[2]			 \n"
		"	fmla	v25.4s, v11.4s, v1.s[2]			 \n"

		"	fmla	v26.4s, v10.4s, v2.s[2]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v27.4s, v11.4s, v2.s[2]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm									 	 \n"


		".macro KERNEL3x16_K3   	                 \n"

		"	fmla	v12.4s, v8.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[3]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v14.4s, v8.4s, v1.s[3]			 \n"
		"	fmla	v15.4s, v9.4s, v1.s[3]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[3]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla	v17.4s, v9.4s, v2.s[3]			 \n"
		"	ldr		q9, [x24], #16					 \n"


		"	fmla	v22.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[3]			 \n"

		"	ldr		q0, [x11], #16					 \n"

		"	fmla	v24.4s, v10.4s, v1.s[3]			 \n"
		"	fmla	v25.4s, v11.4s, v1.s[3]			 \n"

		"	ldr		q1, [x12], #16					 \n"

		"	fmla	v26.4s, v10.4s, v2.s[3]			 \n"
		"	ldr		q10, [x24], #16				 	 \n"
		"	fmla	v27.4s, v11.4s, v2.s[3]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		"	ldr		q2, [x13], #16					 \n"

		".endm									 	 \n"


		".macro KERNEL3x16_END_K   	                 \n"

		"	fmla	v12.4s, v8.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[3]			 \n"

		"	fmla	v14.4s, v8.4s, v1.s[3]			 \n"
		"	fmla	v15.4s, v9.4s, v1.s[3]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[3]			 \n"
		"	fmla	v17.4s, v9.4s, v2.s[3]			 \n"

		"	fmla	v22.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[3]			 \n"

		"	fmla	v24.4s, v10.4s, v1.s[3]			 \n"
		"	fmla	v25.4s, v11.4s, v1.s[3]			 \n"

		"	fmla	v26.4s, v10.4s, v2.s[3]			 \n"
		"	fmla	v27.4s, v11.4s, v2.s[3]			 \n"

		".endm									 	 \n"


		".macro	M3_ADD_C 							 \n"

		"	prfm	PLDL1KEEP, [x25, #64]			 \n"
		"	prfm	PLDL1KEEP, [x26, #64]			 \n"
		"	prfm	PLDL1KEEP, [x27, #64]			 \n"

		"	ldp		q0, q1, [x25]					 \n"

		"	fadd	v12.4s, v12.4s, v0.4s			 \n"
		"	ldp		q2, q3, [x25, #32]				 \n"
		"	fadd	v13.4s, v13.4s, v1.4s			 \n"

		"	fadd	v22.4s, v2.4s, v22.4s			 \n"
		"	ldp		q4, q5, [x26]					 \n"
		"	fadd	v23.4s, v3.4s, v23.4s		 	 \n"

		"	fadd	v14.4s, v4.4s, v14.4s			 \n"
		"	ldp		q6, q7, [x26, #32]				 \n"
		"	fadd	v15.4s, v5.4s, v15.4s			 \n"

		"	prfm	PLDL1KEEP, [x27, #64]			 \n"

		"	fadd	v24.4s, v6.4s, v24.4s			 \n"
		"	ldp		q8, q9, [x27]					 \n"
		"	fadd 	v25.4s, v7.4s, v25.4s			 \n"

		"	fadd	v16.4s, v8.4s, v16.4s			 \n"
		"	ldp		q10, q11, [x27, #32]			 \n"
		"	fadd	v17.4s, v9.4s, v17.4s			 \n"

		"	fadd	v26.4s, v10.4s, v26.4s			 \n"
		"	fadd	v27.4s, v11.4s, v27.4s			 \n"

		".endm 										 \n"


		".macro SAVE3x16							 \n"

		"	stp		q12, q13, [x25]			 		 \n"
		"	stp		q14, q15, [x26]			 	     \n"
		"	stp		q16, q17, [x27]					 \n"

		"	stp		q22, q23, [x25, #32]			 \n"
		"	stp		q24, q25, [x26, #32]			 \n"
		"	stp		q26, q27, [x27, #32]			 \n"

		".endm 									 	 \n"


		".macro	KERNEL2x16_BEGIN_K					 \n"

		"										 	 \n"
		"	ldr		q0, [x11], #16					 \n"
		"	ldr		q1, [x12], #16					 \n"
		"	ldp		q8, q9, [x24], #32			     \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"
		"	prfm	PLDL1KEEP, [x12, #64] 			 \n"

		"	fmul	v12.4s, v8.4s, v0.s[0]	         \n"
		"	fmul	v13.4s, v9.4s, v0.s[0]	         \n"

		"	prfm	PLDL1KEEP, [x24, #128]			 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmul	v14.4s, v8.4s, v1.s[0]	         \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmul	v15.4s, v9.4s, v1.s[0]	         \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmul	v22.4s, v10.4s, v0.s[0]			 \n"
		"	fmul	v23.4s, v11.4s, v0.s[0]			 \n"

		"	fmul	v24.4s, v10.4s, v1.s[0]	         \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmul	v25.4s, v11.4s, v1.s[0]	         \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm 										 \n"


		".macro KERNEL2x16_K0                   	 \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"

		"	fmla	v12.4s, v8.4s, v0.s[0]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[0]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v14.4s, v8.4s, v1.s[0]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla 	v15.4s, v9.4s, v1.s[0]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v0.s[0]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[0]			 \n"

		"	fmla	v24.4s, v10.4s, v1.s[0]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v25.4s, v11.4s, v1.s[0]			 \n"
		"	ldr		q11, [x24], #16					 \n"


		".endm   									 \n"


		".macro KERNEL2x16_K1        	             \n"

		"   prfm    PLDL1KEEP, [x12, #64]       	 \n"
		"	fmla	v12.4s, v8.4s, v0.s[1]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[1]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v14.4s, v8.4s, v1.s[1]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla	v15.4s, v9.4s, v1.s[1]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v0.s[1]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[1]			 \n"

		"	fmla	v24.4s, v10.4s, v1.s[1]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v25.4s, v11.4s, v1.s[1]			 \n"
		"	ldr		q11, [x24], #16					 \n"


		".endm									 	 \n"


		".macro KERNEL2x16_K2          		         \n"

		"	fmla	v12.4s, v8.4s, v0.s[2]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[2]			 \n"

		"	fmla	v14.4s, v8.4s, v1.s[2]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla 	v15.4s, v9.4s, v1.s[2]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v0.s[2]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[2]			 \n"

		"	fmla	v24.4s, v10.4s, v1.s[2]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v25.4s, v11.4s, v1.s[2]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm									 	 \n"


		".macro KERNEL2x16_K3   	                 \n"

		"	fmla	v12.4s, v8.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[3]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v14.4s, v8.4s, v1.s[3]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla	v15.4s, v9.4s, v1.s[3]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[3]			 \n"

		"	ldr		q0, [x11], #16					 \n"

		"	fmla	v24.4s, v10.4s, v1.s[3]			 \n"
		"	ldr		q10, [x24], #16				 	 \n"
		"	fmla	v25.4s, v11.4s, v1.s[3]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		"	ldr		q1, [x12], #16					 \n"

		".endm									 	 \n"


		".macro KERNEL2x16_END_K   	                 \n"

		"	fmla	v12.4s, v8.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[3]			 \n"

		"	fmla	v14.4s, v8.4s, v1.s[3]			 \n"
		"	fmla	v15.4s, v9.4s, v1.s[3]			 \n"

		"	fmla	v22.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[3]			 \n"

		"	fmla	v24.4s, v10.4s, v1.s[3]			 \n"
		"	fmla	v25.4s, v11.4s, v1.s[3]			 \n"

		".endm									 	 \n"


		".macro	M2_ADD_C 							 \n"

		"	prfm	PLDL1KEEP, [x25, #64]			 \n"
		"	prfm	PLDL1KEEP, [x26, #64]			 \n"

		"	ldp		q0, q1, [x25]					 \n"

		"	fadd	v12.4s, v12.4s, v0.4s			 \n"
		"	ldp		q2, q3, [x25, #32]				 \n"
		"	fadd	v13.4s, v13.4s, v1.4s			 \n"

		"	fadd	v22.4s, v2.4s, v22.4s			 \n"
		"	ldp		q4, q5, [x26]					 \n"
		"	fadd	v23.4s, v3.4s, v23.4s		 	 \n"

		"	fadd	v14.4s, v4.4s, v14.4s			 \n"
		"	ldp		q6, q7, [x26, #32]				 \n"
		"	fadd	v15.4s, v5.4s, v15.4s			 \n"


		"	fadd	v24.4s, v6.4s, v24.4s			 \n"
		"	fadd 	v25.4s, v7.4s, v25.4s			 \n"

		".endm 										 \n"


		".macro SAVE2x16							 \n"

		"	stp		q12, q13, [x25]			 		 \n"
		"	stp		q14, q15, [x26]			 	     \n"

		"	stp		q22, q23, [x25, #32]			 \n"
		"	stp		q24, q25, [x26, #32]			 \n"

		".endm 									 	 \n"



		".macro	KERNEL1x16_BEGIN_K					 \n"

		"										 	 \n"
		"	ldr		q0, [x11], #16					 \n"
		"	ldp		q8, q9, [x24], #32			     \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"
		"	prfm	PLDL1KEEP, [x24, #128]			 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmul	v12.4s, v8.4s, v0.s[0]	         \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmul	v13.4s, v9.4s, v0.s[0]	         \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmul	v22.4s, v10.4s, v0.s[0]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmul	v23.4s, v11.4s, v0.s[0]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm 										 \n"


		".macro KERNEL1x16_K0                   	 \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"

		"	fmla	v12.4s, v8.4s, v0.s[0]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla	v13.4s, v9.4s, v0.s[0]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v22.4s, v10.4s, v0.s[0]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v23.4s, v11.4s, v0.s[0]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm   									 \n"


		".macro KERNEL1x16_K1        	             \n"

		"	fmla	v12.4s, v8.4s, v0.s[1]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla	v13.4s, v9.4s, v0.s[1]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v22.4s, v10.4s, v0.s[1]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v23.4s, v11.4s, v0.s[1]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm									 	 \n"


		".macro KERNEL1x16_K2          		         \n"

		"	fmla	v12.4s, v8.4s, v0.s[2]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla	v13.4s, v9.4s, v0.s[2]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"	fmla	v22.4s, v10.4s, v0.s[2]			 \n"
		"	ldr		q10, [x24], #16					 \n"
		"	fmla	v23.4s, v11.4s, v0.s[2]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		".endm									 	 \n"


		".macro KERNEL1x16_K3   	                 \n"

		"	fmla	v12.4s, v8.4s, v0.s[3]			 \n"
		"	ldr		q8, [x24], #16					 \n"
		"	fmla	v13.4s, v9.4s, v0.s[3]			 \n"
		"	ldr		q9, [x24], #16					 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"

		"	fmla	v22.4s, v10.4s, v0.s[3]			 \n"
		"	ldr		q10, [x24], #16				 	 \n"
		"	fmla	v23.4s, v11.4s, v0.s[3]			 \n"
		"	ldr		q11, [x24], #16					 \n"

		"	ldr		q0, [x11], #16					 \n"

		".endm									 	 \n"


		".macro	M1_ADD_C 							 \n"


		"	prfm	PLDL1KEEP, [x25, #64]			 \n"

		"	ldp		q0, q1, [x25]					 \n"

		"	fadd	v12.4s, v12.4s, v0.4s			 \n"
		"	ldp		q2, q3, [x25, #32]				 \n"
		"	fadd	v13.4s, v13.4s, v1.4s			 \n"

		"	fadd	v22.4s, v2.4s, v22.4s			 \n"
		"	fadd	v23.4s, v3.4s, v23.4s		 	 \n"

		".endm 										 \n"


		".macro KERNEL1x16_END_K   	                 \n"

		"	fmla	v12.4s, v8.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[3]			 \n"

		"	fmla	v22.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v23.4s, v11.4s, v0.s[3]			 \n"

		".endm									 	 \n"


		".macro SAVE1x16							 \n"

		"	stp		q12, q13, [x25]			 		 \n"
		"	stp		q22, q23, [x25, #32]			 \n"

		".endm 									 	 \n"


		".macro N8_SAVE5x8							 \n"

		"	subs	x21, x21, #1					 \n"

		"	add 	x10, x10, x5, lsl #4			 \n"
		"	add		x10, x10, x5, lsl #2 			 \n"

		"	stp		q12, q13, [x25]			 		 \n"
		"	add		x25, x29, x6					 \n"
		"	stp		q14, q15, [x26]			 	     \n"
		"	add		x26, x25, x6					 \n"
		"	stp		q16, q17, [x27]					 \n"
		"	add		x27, x26, x6					 \n"
		"	stp		q18, q19, [x28]					 \n"
		"	add		x28, x27, x6					 \n"
		"	stp		q20, q21, [x29]					 \n"
		"	add		x29, x28, x6					 \n"

		".endm 									 	 \n"


		".macro	N8_KERNEL5x8_BEGIN_K  				 \n"

		"	ldr		q0, [x11], #16					 \n"
		"	ldr		q1, [x12], #16					 \n"
		"	ldp		q8, q9, [x24], #32			     \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"
		"	prfm	PLDL1KEEP, [x12, #64] 			 \n"
		"   prfm    PLDL1KEEP, [x13, #64]       	 \n"
		"	prfm	PLDL1KEEP, [x14, #64] 			 \n"
		"	prfm	PLDL1KEEP, [x15, #64]			 \n"

		"	fmul	v12.4s, v8.4s, v0.s[0]	         \n"
		"	fmul	v13.4s, v9.4s, v0.s[0]	         \n"

		"	ldr		q2, [x13], #16					 \n"

		"	fmul	v14.4s, v8.4s, v1.s[0]	         \n"
		"	fmul	v15.4s, v9.4s, v1.s[0]	         \n"

		"	ldr		q3, [x14], #16					 \n"

		"	fmul	v16.4s, v8.4s, v2.s[0]	         \n"
		"	fmul	v17.4s, v9.4s, v2.s[0]	         \n"

		"	prfm	PLDL1KEEP, [x24, #128]			 \n"

		"	ldr		q4, [x15], #16				 	 \n"

		"	fmul	v18.4s, v8.4s, v3.s[0]	         \n"
		"	fmul	v19.4s, v9.4s, v3.s[0]	         \n"

		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmul	v20.4s, v8.4s, v4.s[0]			 \n"
		"	fmul	v21.4s, v9.4s, v4.s[0]			 \n"

		".endm 										 \n"


		".macro N8_KERNEL5x8_K0                   	 \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"

		"	fmla	v12.4s, v8.4s, v0.s[0]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[0]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmla	v14.4s, v8.4s, v1.s[0]			 \n"
		"	fmla 	v15.4s, v9.4s, v1.s[0]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[0]			 \n"
		"	fmla 	v17.4s, v9.4s, v2.s[0]			 \n"

		"	fmla	v18.4s, v8.4s, v3.s[0]			 \n"
		"	fmla 	v19.4s, v9.4s, v3.s[0]			 \n"

		"	fmla	v20.4s, v8.4s, v4.s[0]			 \n"
		"	fmla	v21.4s, v9.4s, v4.s[0]			 \n"

		".endm   									 \n"


		".macro N8_KERNEL5x8_K1        	             \n"

		"   prfm    PLDL1KEEP, [x12, #64]       	 \n"
		"	fmla	v12.4s, v10.4s, v0.s[1]			 \n"
		"	fmla	v13.4s, v11.4s, v0.s[1]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q8, q9, [x24], #32				 \n"

		"	fmla	v14.4s, v10.4s, v1.s[1]			 \n"
		"	fmla	v15.4s, v11.4s, v1.s[1]			 \n"

		"	fmla	v16.4s, v10.4s, v2.s[1]			 \n"
		"	fmla	v17.4s, v11.4s, v2.s[1]			 \n"

		"	fmla	v18.4s, v10.4s, v3.s[1]			 \n"
		"	fmla	v19.4s, v11.4s, v3.s[1]			 \n"

		"	fmla	v20.4s, v10.4s, v4.s[1]			 \n"
		"	fmla	v21.4s, v11.4s, v4.s[1]			 \n"

		".endm									 	 \n"


		".macro N8_KERNEL5x8_K2          		     \n"

		"   prfm    PLDL1KEEP, [x13, #64]       	 \n"

		"	fmla	v12.4s, v8.4s, v0.s[2]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[2]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmla	v14.4s, v8.4s, v1.s[2]			 \n"
		"	fmla 	v15.4s, v9.4s, v1.s[2]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[2]			 \n"
		"	fmla 	v17.4s, v9.4s, v2.s[2]			 \n"

		"	fmla	v18.4s, v8.4s, v3.s[2]			 \n"
		"	fmla 	v19.4s, v9.4s, v3.s[2]			 \n"

		"	fmla	v20.4s, v8.4s, v4.s[2]			 \n"
		"	fmla	v21.4s, v9.4s, v4.s[2]			 \n"

		".endm									 	 \n"


		".macro N8_KERNEL5x8_K3   	                 \n"

		"   prfm    PLDL1KEEP, [x15, #64]       	 \n"
		"	fmla	v12.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v11.4s, v0.s[3]			 \n"

		"	ldr		q0, [x11], #16					 \n"
		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q8, q9, [x24], #32				 \n"

		"	fmla	v14.4s, v10.4s, v1.s[3]			 \n"
		"	fmla	v15.4s, v11.4s, v1.s[3]			 \n"

		"	ldr		q1, [x12], #16					 \n"

		"	fmla	v16.4s, v10.4s, v2.s[3]			 \n"
		"	fmla	v17.4s, v11.4s, v2.s[3]			 \n"

		"	ldr		q2, [x13], #16					 \n"

		"	fmla	v18.4s, v10.4s, v3.s[3]			 \n"
		"	fmla	v19.4s, v11.4s, v3.s[3]			 \n"

		"	ldr		q3, [x14], #16					 \n"

		"	fmla	v20.4s, v10.4s, v4.s[3]			 \n"
		"	fmla	v21.4s, v11.4s, v4.s[3]			 \n"

		"	ldr		q4, [x15], #16					 \n"

		".endm									 	 \n"


		".macro N8_KERNEL5x8_END_K   	             \n"

		"	fmla	v12.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v11.4s, v0.s[3]			 \n"

		"	fmla	v14.4s, v10.4s, v1.s[3]			 \n"
		"	fmla	v15.4s, v11.4s, v1.s[3]			 \n"

		"	fmla	v16.4s, v10.4s, v2.s[3]			 \n"
		"	fmla	v17.4s, v11.4s, v2.s[3]			 \n"

		"	fmla	v18.4s, v10.4s, v3.s[3]			 \n"
		"	fmla	v19.4s, v11.4s, v3.s[3]			 \n"

		"	fmla	v20.4s, v10.4s, v4.s[3]			 \n"
		"	fmla	v21.4s, v11.4s, v4.s[3]			 \n"

		".endm									 	 \n"


		".macro 	N8_KERNEL4x8_BEGIN_K			 \n"

		"										 	 \n"
		"	ldr		q0, [x11], #16					 \n"
		"	ldr		q1, [x12], #16					 \n"
		"	ldp		q8, q9, [x24], #32			     \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"
		"	prfm	PLDL1KEEP, [x12, #64] 			 \n"
		"   prfm    PLDL1KEEP, [x13, #64]       	 \n"
		"	prfm	PLDL1KEEP, [x14, #64] 			 \n"

		"	fmul	v12.4s, v8.4s, v0.s[0]	         \n"
		"	fmul	v13.4s, v9.4s, v0.s[0]	         \n"

		"	ldr		q2, [x13], #16					 \n"

		"	fmul	v14.4s, v8.4s, v1.s[0]	         \n"
		"	fmul	v15.4s, v9.4s, v1.s[0]	         \n"

		"	ldr		q3, [x14], #16					 \n"

		"	fmul	v16.4s, v8.4s, v2.s[0]	         \n"
		"	fmul	v17.4s, v9.4s, v2.s[0]	         \n"

		"	prfm	PLDL1KEEP, [x24, #128]			 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmul	v18.4s, v8.4s, v3.s[0]	         \n"
		"	fmul	v19.4s, v9.4s, v3.s[0]	         \n"

		".endm 										 \n"


		".macro N8_KERNEL4x8_K0                   	 \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"

		"	fmla	v12.4s, v8.4s, v0.s[0]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[0]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmla	v14.4s, v8.4s, v1.s[0]			 \n"
		"	fmla 	v15.4s, v9.4s, v1.s[0]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[0]			 \n"
		"	fmla 	v17.4s, v9.4s, v2.s[0]			 \n"

		"	fmla	v18.4s, v8.4s, v3.s[0]			 \n"
		"	fmla 	v19.4s, v9.4s, v3.s[0]			 \n"


		".endm   									 \n"


		".macro N8_KERNEL4x8_K1        	             \n"

		"   prfm    PLDL1KEEP, [x12, #64]       	 \n"
		"	fmla	v12.4s, v10.4s, v0.s[1]			 \n"
		"	fmla	v13.4s, v11.4s, v0.s[1]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q8, q9, [x24], #32				 \n"

		"	fmla	v14.4s, v10.4s, v1.s[1]			 \n"
		"	fmla	v15.4s, v11.4s, v1.s[1]			 \n"

		"	fmla	v16.4s, v10.4s, v2.s[1]			 \n"
		"	fmla	v17.4s, v11.4s, v2.s[1]			 \n"

		"	fmla	v18.4s, v10.4s, v3.s[1]			 \n"
		"	fmla	v19.4s, v11.4s, v3.s[1]			 \n"


		".endm									 	 \n"


		".macro N8_KERNEL4x8_K2          		     \n"

		"   prfm    PLDL1KEEP, [x13, #64]       	 \n"

		"	fmla	v12.4s, v8.4s, v0.s[2]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[2]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmla	v14.4s, v8.4s, v1.s[2]			 \n"
		"	fmla 	v15.4s, v9.4s, v1.s[2]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[2]			 \n"
		"	fmla 	v17.4s, v9.4s, v2.s[2]			 \n"

		"	fmla	v18.4s, v8.4s, v3.s[2]			 \n"
		"	fmla 	v19.4s, v9.4s, v3.s[2]			 \n"

		".endm									 	 \n"


		".macro N8_KERNEL4x8_K3   	                 \n"

		"   prfm    PLDL1KEEP, [x15, #64]       	 \n"
		"	fmla	v12.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v11.4s, v0.s[3]			 \n"

		"	ldr		q0, [x11], #16					 \n"
		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q8, q9, [x24], #32				 \n"

		"	fmla	v14.4s, v10.4s, v1.s[3]			 \n"
		"	fmla	v15.4s, v11.4s, v1.s[3]			 \n"

		"	ldr		q1, [x12], #16					 \n"

		"	fmla	v16.4s, v10.4s, v2.s[3]			 \n"
		"	fmla	v17.4s, v11.4s, v2.s[3]			 \n"

		"	ldr		q2, [x13], #16					 \n"

		"	fmla	v18.4s, v10.4s, v3.s[3]			 \n"
		"	fmla	v19.4s, v11.4s, v3.s[3]			 \n"

		"	ldr		q3, [x14], #16					 \n"


		".endm									 	 \n"


		".macro N8_KERNEL4x8_END_K   	             \n"

		"	fmla	v12.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v11.4s, v0.s[3]			 \n"

		"	fmla	v14.4s, v10.4s, v1.s[3]			 \n"
		"	fmla	v15.4s, v11.4s, v1.s[3]			 \n"

		"	fmla	v16.4s, v10.4s, v2.s[3]			 \n"
		"	fmla	v17.4s, v11.4s, v2.s[3]			 \n"

		"	fmla	v18.4s, v10.4s, v3.s[3]			 \n"
		"	fmla	v19.4s, v11.4s, v3.s[3]			 \n"

		".endm									 	 \n"


		".macro N8_SAVE4x8 							 \n"

		"	stp		q12, q13, [x25]			 		 \n"
		"	stp		q14, q15, [x26]			 	     \n"
		"	stp		q16, q17, [x27]					 \n"
		"	stp		q18, q19, [x28]					 \n"

		".endm 										 \n"


		".macro 	N8_KERNEL3x8_BEGIN_K			 \n"

		"										 	 \n"
		"	ldr		q0, [x11], #16					 \n"
		"	ldr		q1, [x12], #16					 \n"
		"	ldp		q8, q9, [x24], #32			     \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"
		"	prfm	PLDL1KEEP, [x12, #64] 			 \n"
		"   prfm    PLDL1KEEP, [x13, #64]       	 \n"
		"	prfm	PLDL1KEEP, [x14, #64] 			 \n"

		"	fmul	v12.4s, v8.4s, v0.s[0]	         \n"
		"	fmul	v13.4s, v9.4s, v0.s[0]	         \n"

		"	ldr		q2, [x13], #16					 \n"

		"	fmul	v14.4s, v8.4s, v1.s[0]	         \n"
		"	fmul	v15.4s, v9.4s, v1.s[0]	         \n"

		"	prfm	PLDL1KEEP, [x24, #128]			 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmul	v16.4s, v8.4s, v2.s[0]	         \n"
		"	fmul	v17.4s, v9.4s, v2.s[0]	         \n"

		".endm 										 \n"


		".macro N8_KERNEL3x8_K0                   	 \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"

		"	fmla	v12.4s, v8.4s, v0.s[0]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[0]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmla	v14.4s, v8.4s, v1.s[0]			 \n"
		"	fmla 	v15.4s, v9.4s, v1.s[0]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[0]			 \n"
		"	fmla 	v17.4s, v9.4s, v2.s[0]			 \n"


		".endm   									 \n"


		".macro N8_KERNEL3x8_K1        	             \n"

		"   prfm    PLDL1KEEP, [x12, #64]       	 \n"
		"	fmla	v12.4s, v10.4s, v0.s[1]			 \n"
		"	fmla	v13.4s, v11.4s, v0.s[1]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q8, q9, [x24], #32				 \n"

		"	fmla	v14.4s, v10.4s, v1.s[1]			 \n"
		"	fmla	v15.4s, v11.4s, v1.s[1]			 \n"

		"	fmla	v16.4s, v10.4s, v2.s[1]			 \n"
		"	fmla	v17.4s, v11.4s, v2.s[1]			 \n"


		".endm									 	 \n"


		".macro N8_KERNEL3x8_K2          		     \n"

		"   prfm    PLDL1KEEP, [x13, #64]       	 \n"

		"	fmla	v12.4s, v8.4s, v0.s[2]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[2]			 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmla	v14.4s, v8.4s, v1.s[2]			 \n"
		"	fmla 	v15.4s, v9.4s, v1.s[2]			 \n"

		"	fmla	v16.4s, v8.4s, v2.s[2]			 \n"
		"	fmla 	v17.4s, v9.4s, v2.s[2]			 \n"

		".endm									 	 \n"


		".macro N8_KERNEL3x8_K3   	                 \n"

		"   prfm    PLDL1KEEP, [x15, #64]       	 \n"
		"	fmla	v12.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v11.4s, v0.s[3]			 \n"

		"	ldr		q0, [x11], #16					 \n"
		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q8, q9, [x24], #32				 \n"

		"	fmla	v14.4s, v10.4s, v1.s[3]			 \n"
		"	fmla	v15.4s, v11.4s, v1.s[3]			 \n"

		"	ldr		q1, [x12], #16					 \n"

		"	fmla	v16.4s, v10.4s, v2.s[3]			 \n"
		"	fmla	v17.4s, v11.4s, v2.s[3]			 \n"

		"	ldr		q2, [x13], #16					 \n"


		".endm									 	 \n"


		".macro N8_KERNEL3x8_END_K   	             \n"

		"	fmla	v12.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v11.4s, v0.s[3]			 \n"

		"	fmla	v14.4s, v10.4s, v1.s[3]			 \n"
		"	fmla	v15.4s, v11.4s, v1.s[3]			 \n"

		"	fmla	v16.4s, v10.4s, v2.s[3]			 \n"
		"	fmla	v17.4s, v11.4s, v2.s[3]			 \n"

		".endm									 	 \n"


		".macro N8_SAVE3x8 							 \n"

		"	stp		q12, q13, [x25]			 		 \n"
		"	stp		q14, q15, [x26]			 	     \n"
		"	stp		q16, q17, [x27]					 \n"

		".endm 										 \n"



		".macro  N8_KERNEL2x8_BEGIN_K			     \n"

		"										 	 \n"
		"	ldr		q0, [x11], #16					 \n"
		"	ldr		q1, [x12], #16					 \n"
		"	ldp		q8, q9, [x24], #32			     \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"
		"	prfm	PLDL1KEEP, [x12, #64] 			 \n"

		"	fmul	v12.4s, v8.4s, v0.s[0]	         \n"
		"	fmul	v13.4s, v9.4s, v0.s[0]	         \n"

		"	prfm	PLDL1KEEP, [x24, #128]			 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmul	v14.4s, v8.4s, v1.s[0]	         \n"
		"	fmul	v15.4s, v9.4s, v1.s[0]	         \n"

		".endm 										 \n"


		".macro N8_KERNEL2x8_K0                   	 \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmla	v12.4s, v8.4s, v0.s[0]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[0]			 \n"

		"	fmla	v14.4s, v8.4s, v1.s[0]			 \n"
		"	fmla 	v15.4s, v9.4s, v1.s[0]			 \n"


		".endm   									 \n"


		".macro N8_KERNEL2x8_K1        	             \n"

		"   prfm    PLDL1KEEP, [x12, #64]       	 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q8, q9, [x24], #32				 \n"

		"	fmla	v12.4s, v10.4s, v0.s[1]			 \n"
		"	fmla	v13.4s, v11.4s, v0.s[1]			 \n"

		"	fmla	v14.4s, v10.4s, v1.s[1]			 \n"
		"	fmla	v15.4s, v11.4s, v1.s[1]			 \n"

		".endm									 	 \n"


		".macro N8_KERNEL2x8_K2          		     \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmla	v12.4s, v8.4s, v0.s[2]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[2]			 \n"

		"	fmla	v14.4s, v8.4s, v1.s[2]			 \n"
		"	fmla 	v15.4s, v9.4s, v1.s[2]			 \n"

		".endm									 	 \n"


		".macro N8_KERNEL2x8_K3   	                 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q8, q9, [x24], #32				 \n"

		"	fmla	v12.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v11.4s, v0.s[3]			 \n"

		"	ldr		q0, [x11], #16					 \n"

		"	fmla	v14.4s, v10.4s, v1.s[3]			 \n"
		"	fmla	v15.4s, v11.4s, v1.s[3]			 \n"

		"	ldr		q1, [x12], #16					 \n"

		".endm									 	 \n"


		".macro N8_KERNEL2x8_END_K   	             \n"

		"	fmla	v12.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v11.4s, v0.s[3]			 \n"

		"	fmla	v14.4s, v10.4s, v1.s[3]			 \n"
		"	fmla	v15.4s, v11.4s, v1.s[3]			 \n"

		".endm									 	 \n"


		".macro N8_SAVE2x8 							 \n"

		"	stp		q12, q13, [x25]			 		 \n"
		"	stp		q14, q15, [x26]			 	     \n"

		".endm 										 \n"


		".macro  N8_KERNEL1x8_BEGIN_K			     \n"

		"										 	 \n"
		"	ldr		q0, [x11], #16					 \n"
		"	ldp		q8, q9, [x24], #32			     \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"

		"	prfm	PLDL1KEEP, [x24, #128]			 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmul	v12.4s, v8.4s, v0.s[0]	         \n"
		"	fmul	v13.4s, v9.4s, v0.s[0]	         \n"

		".endm 										 \n"


		".macro N8_KERNEL1x8_K0                   	 \n"

		"   prfm    PLDL1KEEP, [x11, #64]       	 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmla	v12.4s, v8.4s, v0.s[0]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[0]			 \n"
		".endm   									 \n"


		".macro N8_KERNEL1x8_K1        	             \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q8, q9, [x24], #32				 \n"

		"	fmla	v12.4s, v10.4s, v0.s[1]			 \n"
		"	fmla	v13.4s, v11.4s, v0.s[1]			 \n"

		".endm									 	 \n"


		".macro N8_KERNEL1x8_K2          		     \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q10, q11, [x24], #32			 \n"

		"	fmla	v12.4s, v8.4s, v0.s[2]			 \n"
		"	fmla	v13.4s, v9.4s, v0.s[2]			 \n"

		".endm									 	 \n"


		".macro N8_KERNEL1x8_K3   	                 \n"

		"   prfm    PLDL1KEEP, [x24, #128]       	 \n"
		"	ldp		q8, q9, [x24], #32				 \n"

		"	fmla	v12.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v11.4s, v0.s[3]			 \n"

		"	ldr		q0, [x11], #16					 \n"

		".endm									 	 \n"


		".macro N8_KERNEL1x8_END_K   	             \n"

		"	fmla	v12.4s, v10.4s, v0.s[3]			 \n"
		"	fmla	v13.4s, v11.4s, v0.s[3]			 \n"

		".endm									 	 \n"


		".macro N8_SAVE1x8 							 \n"

		"	stp		q12, q13, [x25]			 		 \n"

		".endm 										 \n"




//----------------------------------------------------

		"SMM:									 	 \n"

		"	ldr		x0, %[C]						 \n"
		"	ldr		x1, %[A]						 \n"
		"	ldr		x2, %[B]						 \n"

		"	ldr		x3, %[M]						 \n"
		"	ldr		x4, %[N]						 \n"
		"	ldr		x5, %[K]						 \n"
//		"	ldr		x7, %[temp]						 \n"
		"	ldr		x9, %[LN] 						 \n"
		"	ldr		x6, %[LK]						 \n"

		"	ldr		x19, %[SB]						 \n"
		"	ldr		x8, %[k_tag] 					 \n"
//		"	lsl		x6, x4, #2						 \n"  //sizeof(N)

		"	add		sp, sp, #-32					 \n"

		"	mov		x23, #5						 	 \n"
//		"	lsl		x8, x5, #2						 \n"  //sizeof(K)

		"   prfm    PLDL1KEEP, [x1]             	 \n"
		"   prfm    PLDL1KEEP, [x2]             	 \n"

		"	udiv	x30, x3, x23				 	 \n"	// M / 5
		"	lsr		x20, x4, #4					 	 \n"	// N / 16

		"	msub	x23, x30, x23, x3 				 \n"	// M % 5
		"	str 	x23, [sp] 						 \n"
		"	mov 	x23, x19 						 \n"    //SB
		"	str  	x8, [sp, #16]					 \n"

//		"	cmp		x20, #0							 \n"
//		"	beq		BEGIN_N8						 \n"



//-----------------------------------------------N16
		"BEGIN_N16:								 	 \n"

		"	mov 	x25, x0   						 \n"   //C1*
		"	add		x26, x25, x9, lsl #2 			 \n"   //C2*
		"	add 	x27, x25, x9, lsl #3 			 \n"   //C3*
		" 	add 	x28, x26, x9, lsl #3 			 \n"   //C4*
		"	add		x29, x27, x9, lsl #3 			 \n"   //C5*

		"	mov		x10, x1   						 \n"
		"	mov		x21, x30  						 \n"
		"	mov		x24, x23						 \n"   //还原SB的地址

		"	mov		x7, #4							 \n"   //4次B的循环
		"	mov		x8, #16							 \n"

		"BEGIN_PACKB:								 \n"

		"	mov		x16, x2						 	 \n"   //B0*
		"	add		x17, x16, x6, lsl #2 			 \n"
		"	add		x18, x17, x6, lsl #2 			 \n"
		"	add		x19, x18, x6, lsl #2 			 \n"

		"	mov		x11, x10						 \n"    //A0*
		"	add		x12, x11, x6, lsl #2			 \n"    //A1*
		"	add		x13, x12, x6, lsl #2			 \n"	//A2*
		"	add		x14, x13, x6, lsl #2			 \n"	//A3*
		"	add		x15, x14, x6, lsl #2 			 \n"	//A4*

		"	prfm    PLDL1KEEP, [x16, #64]			 \n"
		"	prfm    PLDL1KEEP, [x17, #64]			 \n"
		"	prfm    PLDL1KEEP, [x18, #64]			 \n"
		"	prfm    PLDL1KEEP, [x19, #64]			 \n"

		"	prfm    PLDL1KEEP, [x11, #64]			 \n"
		"	prfm    PLDL1KEEP, [x12, #64]			 \n"
		"	prfm    PLDL1KEEP, [x13, #64]			 \n"
		"	prfm    PLDL1KEEP, [x14, #64]			 \n"
		"	prfm    PLDL1KEEP, [x15, #64]			 \n"

		"PACK_Body_K:								 \n"

		"	lsr		x22, x5, #3 					 \n"     // K / 8

		"	PACK_KERNEL5x4_BEGIN_K				 	 \n"

		"	subs	x22, x22, #1		     		 \n"		
		"	b 		PACK_K1_7						 \n"

		"PACK_K:									 \n"
		
		"	PACK_KERNEL5x4_K0						 \n"
		"PACK_K1_7:									 \n"

		"	beq		PACK_Edge_K						 \n"

		"	PACK_KERNEL5x4_K1						 \n"
		
		"	subs	x22, x22, #1			 		 \n"
		"	b 		PACK_K			 				 \n"	

		"PACK_Edge_K:							     \n"


		"	prfm	PLDL1KEEP, [x25, #64]			 \n"
		"	prfm	PLDL1KEEP, [x26, #64]			 \n"
		"	prfm	PLDL1KEEP, [x27, #64]			 \n"
		"	prfm	PLDL1KEEP, [x28, #64]			 \n"
		"	prfm	PLDL1KEEP, [x29, #64]			 \n"

		"	PACK_KERNEL5x4_END_K			         \n"		

		"	ldr		x8, [sp, #16]					 \n"	
		"	cmp		x8, #0							 \n"
		"	beq		PACKB_SAVE1 					 \n"
		"	PACKB_ADD_C 							 \n"
		"PACKB_SAVE1: 								 \n"
		"	SAVE5x4								 	 \n"
		"	mov		x8, #16							 \n"

//		"	beq		END_PACKB						 \n"

		"	add		x23, x23, #16					 \n"
		"	mov		x24, x23 						 \n"
		"	add		x2, x2, x6, lsl #4				 \n"

		"	bgt  	BEGIN_PACKB					 	 \n"

		"END_PACKB:									 \n"

		"	sub		x23, x23, x8, lsl #2			 \n"    //还原SB的索引

		"	sub 	x29, x29, x8, lsl #2			 \n"    //C矩阵的偏移量还原
		"	add		x25, x29, x9, lsl #2			 \n"
		"	add		x26, x25, x9, lsl #2			 \n"
		"	add		x27, x26, x9, lsl #2			 \n"
		"	add		x28, x27, x9, lsl #2			 \n"
		"	add		x29, x28, x9, lsl #2 			 \n"

		"	add		x10, x10, x6, lsl #4			 \n"  
		"	add 	x10, x10, x6, lsl #2 			 \n"	// A + 5行

		"	cmp		x8, #16							 \n"
		"	bne 	N8_END_PACKB					 \n"

		"	subs	x21, x21, #1					 \n"
		"	beq		END_M5							 \n"


		//---------------------------------------------------

		"BEGIN_M5:									 \n"

		"	mov		x24, x23	     				 \n"

		"	mov		x11, x10						 \n"
		"	add		x12, x11, x6, lsl #2			 \n"
		"	add		x13, x12, x6, lsl #2			 \n"
		"	add		x14, x13, x6, lsl #2			 \n"
		"	add		x15, x14, x6, lsl #2 			 \n"

		"	prfm	PLDL1KEEP, [x24, #512]			 \n"

		"	prfm    PLDL1KEEP, [x11, #64]			 \n"
		"	prfm    PLDL1KEEP, [x12, #64]			 \n"
		"	prfm    PLDL1KEEP, [x13, #64]			 \n"
		"	prfm    PLDL1KEEP, [x14, #64]			 \n"
		"	prfm    PLDL1KEEP, [x15, #64]			 \n"


		"Body_K:								 	 \n"

		"	lsr		x22, x5, #3 					 \n"     // K / 8
		"	KERNEL5x16_BEGIN_K						 \n"
		"	subs	x22, x22, #1		     		 \n"	
		"	b K1_7									 \n"

		"Main_K:									 \n"
		

		"	KERNEL5x16_K0						 	 \n"
		"K1_7:										 \n"
		
		"	KERNEL5x16_K1							 \n"
		"	KERNEL5x16_K2							 \n"
		"	KERNEL5x16_K3							 \n"
		"	KERNEL5x16_K4							 \n"
		"	KERNEL5x16_K5							 \n"
		"	KERNEL5x16_K6							 \n"

		"	beq		Edge_K							 \n"

		"	KERNEL5x16_K7							 \n"
		
		"	subs	x22, x22, #1			 		 \n"
		"	b 		Main_K			 				 \n"	

		"Edge_K:									 \n"


		"	prfm	PLDL1KEEP, [x25, #64]			 \n"
		"	prfm	PLDL1KEEP, [x26, #64]			 \n"
		"	prfm	PLDL1KEEP, [x27, #64]			 \n"
		"	prfm	PLDL1KEEP, [x28, #64]			 \n"
		"	prfm	PLDL1KEEP, [x29, #64]			 \n"

		"	KERNEL5x16_END_K						 \n"

		"	ldr		x8, [sp, #16]					 \n"	
		"	cmp		x8, #0							 \n"
		"	beq		M5_SAVE1 						 \n"
		"	ADD_C 								 	 \n"
		"M5_SAVE1: 									 \n"
		"	SAVE5x16								 \n"	

//		"	SAVE5x16								 \n"
		"	bgt   	BEGIN_M5						 \n"

		"END_M5:									 \n"


		"	mov		x24, x23	     				 \n"  //B0*

		"	ldr		x21, [sp]					 	 \n"
		"	cmp		x21, #4							 \n"
		"	bne 	BEGIN_M3 						 \n"



	//--------------------------------------------------------
		"BEGIN_M4:						 			 \n"

		"	mov		x11, x10 						 \n"
		"	add		x12, x11, x6, lsl #2 		     \n"
		"	add		x13, x12, x6, lsl #2 			 \n"
		"	add		x14, x13, x6, lsl #2 			 \n"

		"	prfm    PLDL1KEEP, [x11, #64]			 \n"
		"	prfm    PLDL1KEEP, [x12, #64]			 \n"
		"	prfm    PLDL1KEEP, [x13, #64]			 \n"
		"	prfm    PLDL1KEEP, [x14, #64]			 \n"


		"M4_Body_K:								 	 \n"

		"	lsr		x22, x5, #2 					 \n"     // K / 8
		"	KERNEL4x16_BEGIN_K						 \n"
		"	subs	x22, x22, #1		     		 \n"	
		"	b 		M4_K1_3							 \n"

		"M4_Main_K:									 \n"
		
		"	KERNEL4x16_K0						 	 \n"
		"M4_K1_3:									 \n"
		
		"	KERNEL4x16_K1							 \n"
		"	KERNEL4x16_K2							 \n"

		"	beq		M4_Edge_K						 \n"

		"	KERNEL4x16_K3							 \n"
		
		"	subs	x22, x22, #1			 		 \n"
		"	b 		M4_Main_K			 			 \n"	

		"M4_Edge_K:									 \n"


		"	prfm	PLDL1KEEP, [x25, #64]			 \n"
		"	prfm	PLDL1KEEP, [x26, #64]			 \n"
		"	prfm	PLDL1KEEP, [x27, #64]			 \n"
		"	prfm	PLDL1KEEP, [x28, #64]			 \n"

		"	KERNEL4x16_END_K						 \n"

		"	ldr		x8, [sp, #16]					 \n"	
		"	cmp		x8, #0							 \n"
		"	beq		M4_SAVE1 						 \n"
		"	M4_ADD_C 								 \n"
		"M4_SAVE1: 									 \n"
		"	SAVE4x16								 \n"

		"	b 		END_M 							 \n"


		//--------------------------------------------------------

		"BEGIN_M3:			 						 \n"
		"	cmp		x21, #3							 \n"
		"	bne 	BEGIN_M2 						 \n"

		"	mov		x11, x10 						 \n"
		"	add		x12, x11, x6, lsl #2 			 \n"
		"	add		x13, x12, x6, lsl #2 			 \n"

		"	prfm    PLDL1KEEP, [x11, #64]			 \n"
		"	prfm    PLDL1KEEP, [x12, #64]			 \n"
		"	prfm    PLDL1KEEP, [x13, #64]			 \n"

		"M3_Body_K:								 	 \n"

		"	lsr		x22, x5, #2 					 \n"     // K / 8
		"	KERNEL3x16_BEGIN_K						 \n"
		"	subs	x22, x22, #1		     		 \n"	
		"	b 		M3_K1_3							 \n"

		"M3_Main_K:									 \n"
		
		"	KERNEL3x16_K0						 	 \n"
		"M3_K1_3:									 \n"
		
		"	KERNEL3x16_K1							 \n"
		"	KERNEL3x16_K2							 \n"

		"	beq		M3_Edge_K						 \n"

		"	KERNEL3x16_K3							 \n"
		
		"	subs	x22, x22, #1			 		 \n"
		"	b 		M3_Main_K			 			 \n"	

		"M3_Edge_K:									 \n"

		"	prfm	PLDL1KEEP, [x25, #64]			 \n"
		"	prfm	PLDL1KEEP, [x26, #64]			 \n"
		"	prfm	PLDL1KEEP, [x27, #64]			 \n"

		"	KERNEL3x16_END_K						 \n"	

		"	ldr		x8, [sp, #16]					 \n"	
		"	cmp		x8, #0							 \n"
		"	beq		M3_SAVE1 						 \n"
		"	M3_ADD_C 								 \n"
		"M3_SAVE1: 									 \n"
		"	SAVE3x16								 \n"

		"	b 		END_M 							 \n"




//----------------------------------------------------------
		"BEGIN_M2:			 						 \n"

		"	cmp		x21, #2							 \n"
		"	bne 	BEGIN_M1 						 \n"

		"	mov		x11, x10 						 \n"
		"	add		x12, x11, x6, lsl #2 			 \n"

		"	prfm    PLDL1KEEP, [x11, #64]			 \n"
		"	prfm    PLDL1KEEP, [x12, #64]			 \n"

		"M2_Body_K:								 	 \n"

		"	lsr		x22, x5, #2 					 \n"     // K / 8
		"	KERNEL2x16_BEGIN_K						 \n"
		"	subs	x22, x22, #1		     		 \n"	
		"	b 		M2_K1_3							 \n"

		"M2_Main_K:									 \n"
		
		"	KERNEL2x16_K0						 	 \n"
		"M2_K1_3:									 \n"
		
		"	KERNEL2x16_K1							 \n"
		"	KERNEL2x16_K2							 \n"

		"	beq		M2_Edge_K						 \n"

		"	KERNEL2x16_K3							 \n"
		
		"	subs	x22, x22, #1			 		 \n"
		"	b 		M2_Main_K			 			 \n"	

		"M2_Edge_K:									 \n"

		"	prfm	PLDL1KEEP, [x25, #64]			 \n"
		"	prfm	PLDL1KEEP, [x26, #64]			 \n"

		"	KERNEL2x16_END_K						 \n"

		"	ldr		x8, [sp, #16]					 \n"	
		"	cmp		x8, #0							 \n"
		"	beq		M2_SAVE1 						 \n"
		"	M2_ADD_C 								 \n"
		"M2_SAVE1: 									 \n"
		"	SAVE2x16								 \n"

		"	b 		END_M 							 \n"




//---------------------------------------------------------		

		"BEGIN_M1:									 \n"

		"	cmp		x21, #1							 \n"
		"	bne 	END_M 						 	 \n"

		"	mov		x11, x10 						 \n"
		"	prfm    PLDL1KEEP, [x11, #64]			 \n"

		"M1_Body_K:								 	 \n"

		"	lsr		x22, x5, #2 					 \n"     // K / 8
		"	KERNEL1x16_BEGIN_K						 \n"
		"	subs	x22, x22, #1		     		 \n"	
		"	b 		M1_K1_3							 \n"

		"M1_Main_K:									 \n"
		
		"	KERNEL1x16_K0						 	 \n"
		"M1_K1_3:									 \n"
		
		"	KERNEL1x16_K1							 \n"
		"	KERNEL1x16_K2							 \n"

		"	beq		M1_Edge_K						 \n"

		"	KERNEL1x16_K3							 \n"
		
		"	subs	x22, x22, #1			 		 \n"
		"	b 		M1_Main_K			 			 \n"	

		"M1_Edge_K:									 \n"

		"	prfm	PLDL1KEEP, [x25, #64]			 \n"

		"	KERNEL1x16_END_K						 \n"

		"	ldr		x8, [sp, #16]					 \n"	
		"	cmp		x8, #0							 \n"
		"	beq		M1_SAVE1 						 \n"
		"	M1_ADD_C 								 \n"
		"M1_SAVE1: 									 \n"

		"	SAVE1x16								 \n"

		"END_M:										 \n"


		"	subs	x20, x20, #1					 \n"

		"	add		x16, x16, #64					 \n"
		"	add		x0, x0, #64						 \n"

		"	bgt		BEGIN_N16						 \n"

		"END_N16:									 \n"

		"	ands	x20, x4, #15					 \n"
		"	beq		END_N 							 \n"


	    "N8_END_PACKB:	    						 \n"
	/*	

		"BEGIN_N8:									\n"


//----------------------------------------------------------N8
		"N8_BEGIN_PACKB:							 \n"

		"	mov 	x25, x0   						 \n"   //C1*
		"	add		x26, x25, x6 					 \n"   //C2*
		"	add 	x27, x25, x6, lsl #1 			 \n"   //C3*
		" 	add 	x28, x26, x6, lsl #1 			 \n"   //C4*
		"	add		x29, x27, x6, lsl #1 			 \n"   //C5*

		"	mov		x10, x1   						 \n"   //A0*
		"	mov		x21, x30  						 \n"   // M / 5
		"	mov		x7, #2							 \n"
		"	mov		x24, x23						 \n"

		"	mov		x8, #8 							 \n"

		"	b 		BEGIN_PACKB 					 \n"

		"N8_END_PACKB:								 \n"

		"	subs	x21, x21, #1					 \n"
		"	beq		N8_END_M5						 \n"


//--------------------------------------------------N8M5
		"N8_BEGIN_M5:								 \n"

		"	mov		x24, x23	     				 \n"

		"	mov		x11, x10						 \n"
		"	add		x12, x11, x5, lsl #2			 \n"
		"	add		x13, x12, x5, lsl #2			 \n"
		"	add		x14, x13, x5, lsl #2			 \n"
		"	add		x15, x14, x5, lsl #2 			 \n"

		"	prfm    PLDL1KEEP, [x11, #64]			 \n"
		"	prfm    PLDL1KEEP, [x12, #64]			 \n"
		"	prfm    PLDL1KEEP, [x13, #64]			 \n"
		"	prfm    PLDL1KEEP, [x14, #64]			 \n"
		"	prfm    PLDL1KEEP, [x15, #64]			 \n"


		"N8_Body_K:								 	 \n"

		"	lsr		x22, x5, #2 					 \n"     // K / 8
		"	N8_KERNEL5x8_BEGIN_K					 \n"
		"	subs	x22, x22, #1		     		 \n"	
		"	b 		N8_K1_3							 \n"

		"N8_Main_K:									 \n"
		

		"	N8_KERNEL5x8_K0						 	 \n"
		"N8_K1_3:									 \n"
		
		"	N8_KERNEL5x8_K1							 \n"
		"	N8_KERNEL5x8_K2							 \n"

		"	beq		N8_Edge_K						 \n"

		"	N8_KERNEL5x8_K3							 \n"
		
		"	subs	x22, x22, #1			 		 \n"
		"	b 		N8_Main_K			 			 \n"	

		"N8_Edge_K:									 \n"


		"	prfm	PLDL1KEEP, [x25, #64]			 \n"
		"	prfm	PLDL1KEEP, [x26, #64]			 \n"
		"	prfm	PLDL1KEEP, [x27, #64]			 \n"
		"	prfm	PLDL1KEEP, [x28, #64]			 \n"
		"	prfm	PLDL1KEEP, [x29, #64]			 \n"

		"	N8_KERNEL5x8_END_K						 \n"		

		"	N8_SAVE5x8								 \n"
		"	bgt   	N8_BEGIN_M5					 	 \n"





//---------------------------------------------------------

		"N8_END_M5:									 \n"

		"	mov		x24, x23	     				 \n"  //B0*

		"	ldr		x21, [sp]						 \n"
		"	cmp		x21, #4							 \n"
		"	bne 	N8_BEGIN_M3 					 \n"

	//--------------------------------------------------------
		"N8_BEGIN_M4:						 		 \n"

		"	mov		x11, x10 						 \n"
		"	add		x12, x11, x5, lsl #2 			 \n"
		"	add		x13, x12, x5, lsl #2 			 \n"
		"	add		x14, x13, x5, lsl #2 			 \n"

		"	prfm    PLDL1KEEP, [x11, #64]			 \n"
		"	prfm    PLDL1KEEP, [x12, #64]			 \n"
		"	prfm    PLDL1KEEP, [x13, #64]			 \n"
		"	prfm    PLDL1KEEP, [x14, #64]			 \n"


		"N8_M4_Body_K:								 \n"

		"	lsr		x22, x5, #2 					 \n"     // K / 8
		"	N8_KERNEL4x8_BEGIN_K					 \n"
		"	subs	x22, x22, #1		     		 \n"	
		"	b 		N8_M4_K1_3						 \n"

		"N8_M4_Main_K:								 \n"
		
		"	N8_KERNEL4x8_K0						 	 \n"
		"N8_M4_K1_3:								 \n"
		
		"	N8_KERNEL4x8_K1						 	 \n"
		"	N8_KERNEL4x8_K2						 	 \n"

		"	beq		N8_M4_Edge_K					 \n"

		"	N8_KERNEL4x8_K3						 	 \n"
		
		"	subs	x22, x22, #1			 		 \n"
		"	b 		N8_M4_Main_K			 		 \n"	

		"N8_M4_Edge_K:								 \n"


		"	prfm	PLDL1KEEP, [x25, #32]			 \n"
		"	prfm	PLDL1KEEP, [x26, #32]			 \n"
		"	prfm	PLDL1KEEP, [x27, #32]			 \n"
		"	prfm	PLDL1KEEP, [x28, #32]			 \n"

		"	N8_KERNEL4x8_END_K						 \n"		
		"	N8_SAVE4x8								 \n"

		"	b 		N8_END_M 						 \n"


//------------------------------------------------------------------

		"N8_BEGIN_M3: 								 \n"

		"	cmp		x21, #3							 \n"
		"	bne 	N8_BEGIN_M2 					 \n"

		"	mov		x11, x10 						 \n"
		"	add		x12, x11, x5, lsl #2 			 \n"
		"	add		x13, x12, x5, lsl #2 			 \n"

		"	prfm    PLDL1KEEP, [x11, #64]			 \n"
		"	prfm    PLDL1KEEP, [x12, #64]			 \n"
		"	prfm    PLDL1KEEP, [x13, #64]			 \n"


		"N8_M3_Body_K:								 \n"

		"	lsr		x22, x5, #2 					 \n"     // K / 8
		"	N8_KERNEL3x8_BEGIN_K					 \n"
		"	subs	x22, x22, #1		     		 \n"	
		"	b 		N8_M3_K1_3						 \n"

		"N8_M3_Main_K:								 \n"
		
		"	N8_KERNEL3x8_K0						 	 \n"
		"N8_M3_K1_3:								 \n"
		
		"	N8_KERNEL3x8_K1						 	 \n"
		"	N8_KERNEL3x8_K2						 	 \n"

		"	beq		N8_M3_Edge_K					 \n"

		"	N8_KERNEL3x8_K3						 	 \n"
		
		"	subs	x22, x22, #1			 		 \n"
		"	b 		N8_M3_Main_K			 		 \n"	

		"N8_M3_Edge_K:								 \n"


		"	prfm	PLDL1KEEP, [x25, #32]			 \n"
		"	prfm	PLDL1KEEP, [x26, #32]			 \n"
		"	prfm	PLDL1KEEP, [x27, #32]			 \n"

		"	N8_KERNEL3x8_END_K						 \n"		
		"	N8_SAVE3x8								 \n"

		"	b 		N8_END_M 						 \n"





//--------------------------------------------------------

		"N8_BEGIN_M2:								 \n"


		"	cmp		x21, #2							 \n"
		"	bne 	N8_BEGIN_M1 					 \n"

		"	mov		x11, x10 						 \n"
		"	add		x12, x11, x5, lsl #2 			 \n"

		"	prfm    PLDL1KEEP, [x11, #64]			 \n"
		"	prfm    PLDL1KEEP, [x12, #64]			 \n"


		"N8_M2_Body_K:								 \n"

		"	lsr		x22, x5, #2 					 \n"     // K / 8
		"	N8_KERNEL2x8_BEGIN_K					 \n"
		"	subs	x22, x22, #1		     		 \n"	
		"	b 		N8_M2_K1_3						 \n"

		"N8_M2_Main_K:								 \n"
		
		"	N8_KERNEL2x8_K0						 	 \n"
		"N8_M2_K1_3:								 \n"
		
		"	N8_KERNEL2x8_K1						 	 \n"
		"	N8_KERNEL2x8_K2						 	 \n"

		"	beq		N8_M2_Edge_K					 \n"

		"	N8_KERNEL2x8_K3						 	 \n"
		
		"	subs	x22, x22, #1			 		 \n"
		"	b 		N8_M2_Main_K			 		 \n"	

		"N8_M2_Edge_K:								 \n"


		"	prfm	PLDL1KEEP, [x25, #32]			 \n"
		"	prfm	PLDL1KEEP, [x26, #32]			 \n"

		"	N8_KERNEL2x8_END_K						 \n"		
		"	N8_SAVE2x8								 \n"

		"	b 		N8_END_M 						 \n"





//-----------------------------------------------------
		"N8_BEGIN_M1:								 \n"


		"	cmp		x21, #1							 \n"
		"	bne 	N8_END_M 					 	 \n"

		"	mov		x11, x10 						 \n"

		"	prfm    PLDL1KEEP, [x11, #64]			 \n"

		"N8_M1_Body_K:								 \n"

		"	lsr		x22, x5, #2 					 \n"     // K / 8
		"	N8_KERNEL1x8_BEGIN_K					 \n"
		"	subs	x22, x22, #1		     		 \n"	
		"	b 		N8_M1_K1_3						 \n"

		"N8_M1_Main_K:								 \n"
		
		"	N8_KERNEL1x8_K0						 	 \n"
		"N8_M1_K1_3:								 \n"
		
		"	N8_KERNEL1x8_K1						 	 \n"
		"	N8_KERNEL1x8_K2						 	 \n"

		"	beq		N8_M1_Edge_K					 \n"

		"	N8_KERNEL1x8_K3						 	 \n"
		
		"	subs	x22, x22, #1			 		 \n"
		"	b 		N8_M1_Main_K			 		 \n"	

		"N8_M1_Edge_K:								 \n"

		"	prfm	PLDL1KEEP, [x25, #32]			 \n"

		"	N8_KERNEL1x8_END_K						 \n"		
		"	N8_SAVE1x8								 \n"

		"N8_END_M: 									 \n"
*/
		"END_N:									 	 \n"

		"	add		sp, sp, #32						 \n"
		
		:
		:	
			[C] "m" (C),
			[A] "m" (A),
            [B] "m" (B), 
            [M] "m" (M),
            [N] "m" (N),
            [K] "m" (K),
            [LN] "m" (LN),
            [LK] "m" (LK),
            [SB] "m" (SB),
            [k_tag] "m" (k_tag)
        :   "x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7", "x8",
        	"x9", "x10", "x11", "x12", "x13","x14", "x15", "x16",
        	"x17", "x18", "x19", "x20", "x21", "x22", "x23", "x24","x25",
        	"x26", "x27", "x28", "x29", "x30",
            "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7",
            "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15",
            "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23",
            "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31"

		);
}

void Small_SGEMM(float *C, float *A, float *B, long M, long N, 
					long K, long *temp, long LD)
{

	omp_set_num_threads(num);
	long i, k, kc;
	long LK = K;
    long GEMM_K = 328;
    void *ptr;
    posix_memalign(&ptr, 64, num * GEMM_K * 16  *sizeof( float ));
    float *SSB = (float *)ptr;

	#   pragma omp parallel for private(k,kc)
	for(i=0; i< LD; i= i + N)
	{
		float *CC = C + i ;

		for(k = 0; k < LK; k = k + kc)
		{ 
			kc = GEMM_K;
			if(LK - k < GEMM_K)
				kc = LK - k;
			float * AA = A + k;
			float *BB = B + i * LK + k ;

			SMM(CC, AA, BB, M, N, kc, temp, LD, LK, 
				&SSB[i/N * GEMM_K * 16], k);
		}
	}

	free(SSB);
	
}

int main()
{

	openblas_set_num_threads(num);

	int i,j,k;
	int loop=5;
	long M, N, K;
	double start, cost;
	int flag =0 ;
	void *ptr, *ptr1;
	long temp =-1;
	int pc;

	FILE *fp;
  	if( (fp=fopen("NSMM_P_FT.txt","w")) == NULL )
  	{
    	puts("Fail to open file!");
    	exit(0);
  	}

	K = 576;
	for(j = 5; j < 6;j++)
	{
                M = 262;      
                N = 50176;
//		K = 4992 + 8 * j; 
		double ops = M *N *K * 1.0e-09 * 2;

		fprintf(fp, "%d %d %d", M,N,K);
		for(pc =0; pc < 5; pc++)
		{
			posix_memalign(&ptr1, 4096, M* K * sizeof( float ));
			posix_memalign(&ptr, 4096, K* N * sizeof( float ));
			float *A = (float *)ptr1;	
			float *B = (float *)ptr;
		    float *C = ( float * ) malloc( M* N * sizeof( float ) );

		    random_matrix(M,K,A);
		    random_matrix(K,N,B);
		   // transpose(K, N, B);

		    for( i =0 ;i< 2; i++)
		    	Small_SGEMM(C, A, B, M, N/num, K, &temp, N);

			start = dclock();
			for( i= 0; i< loop ;i++)
				Small_SGEMM(C, A, B, M, N/num, K, &temp, N);
			cost =(dclock()-start)/loop; 

			ops = M * N  * K * 1.0e-09 * 2;
			printf("\nN_SMM:  M= %d N=%d K=%d flops = %lf effic= %.3lf %\n", 
					M, N, K, ops/cost, ops/cost/17.6 * 100/num);


			fprintf(fp, " %.3f", ops/cost);
		    free(A);
		    free(B);
		    free(C);
		}

		fprintf(fp, "\n");
	}

	fclose(fp);
    return 0;

}
