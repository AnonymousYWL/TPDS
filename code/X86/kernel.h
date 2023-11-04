void SMM_NN_KERNEL12x16(float *C, float *A, float *B, long M, 
						long N, long K, long LN, long LK, float *Bc, long k_tag)
{

	asm volatile(


		".macro	KERNEL12x16_PACK_K1							\n"

		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm4, %%zmm20 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm4, %%zmm21 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	16(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm4, %%zmm22 		\n"

		"   vbroadcastss	20(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm4, %%zmm23 		\n"

		"   vbroadcastss	24(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm4, %%zmm24 		\n"

		"   vbroadcastss	28(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm4, %%zmm25 		\n"

		"   vbroadcastss	32(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm4, %%zmm26 		\n"

		"	leaq  	(%%rbx, %%r8, 4), %%rbx 				\n"  // B

		"   vbroadcastss	36(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm4, %%zmm27 		\n"

		"   vbroadcastss	40(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm4, %%zmm28 		\n"

		"   vbroadcastss	44(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm4, %%zmm29 		\n"
		"   vmovups 		(%%rbx), %%zmm6        			\n" 
		"	addq  			$48, %%rax 						\n"

		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vfmadd231ps		%%zmm2, %%zmm4, %%zmm30 		\n"

		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm4, %%zmm31 		\n"
		"   vmovups 		%%zmm4, (%%rbp)       			\n"
		"	addq  			$64, %%rbp 						\n"

		
		".endm 												\n"


		".macro	KERNEL12x16_PACK_K2							\n"

		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm20 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"	
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm21 		\n"

		"   vbroadcastss	16(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm22 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	20(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm23 		\n"

		"   vbroadcastss	24(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm24 		\n"

		"   vbroadcastss	28(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm25 		\n"

		"   vbroadcastss	32(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm26 		\n"

		"	leaq  	(%%rbx, %%r8, 4), %%rbx 				\n"  // B

		"   vbroadcastss	36(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm27 		\n"

		"   prefetcht0 		64(%%rbx)                 		\n"

		"   vbroadcastss	40(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm28 		\n"

		"   vbroadcastss	44(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm29 		\n"
		"   vmovups 		(%%rbx), %%zmm4        			\n" 
		"	addq  			$48, %%rax 						\n"

		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm30 		\n"

		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm31 		\n"
		"   vmovups 		%%zmm6, (%%rbp)       			\n"
		"	addq  			$64, %%rbp 						\n"


		".endm 												\n"



		".macro	KERNEL12x16_PACK_END_K						\n"

		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm20 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"	
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm21 		\n"

		"   vbroadcastss	16(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm22 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	20(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm23 		\n"

		"   vbroadcastss	24(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm24 		\n"

		"   vbroadcastss	28(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm25 		\n"

		"   vbroadcastss	32(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm26 		\n"

		"   vbroadcastss	36(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm27 		\n"

		"   vbroadcastss	40(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm28 		\n"

		"   vbroadcastss	44(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm29 		\n"
		"	addq  			$48, %%rax 						\n"

		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm30 		\n"
		"   vmovups 		%%zmm6, (%%rbp)       			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm31 		\n"


		".endm 												\n"



		".macro	KERNEL12x16_K1								\n"

		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm4, %%zmm20 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm4, %%zmm21 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	16(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm4, %%zmm22 		\n"

		"   vbroadcastss	20(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm4, %%zmm23 		\n"

		"   vbroadcastss	24(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm4, %%zmm24 		\n"

		"   vbroadcastss	28(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm4, %%zmm25 		\n"

		"   vbroadcastss	32(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm4, %%zmm26 		\n"

		"	addq  			$64, %%rbx 						\n"  //B

		"   vbroadcastss	36(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm4, %%zmm27 		\n"

		"   vbroadcastss	40(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm4, %%zmm28 		\n"

		"   vbroadcastss	44(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm4, %%zmm29 		\n"
		"   vmovups 		(%%rbx), %%zmm6        			\n" 
		"	addq  			$48, %%rax 						\n"

		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vfmadd231ps		%%zmm2, %%zmm4, %%zmm30 		\n"

		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm4, %%zmm31 		\n"
		
		".endm 												\n"


		".macro	KERNEL12x16_K2								\n"

		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm20 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"	
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm21 		\n"

		"   vbroadcastss	16(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm22 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	20(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm23 		\n"

		"   vbroadcastss	24(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm24 		\n"

		"   vbroadcastss	28(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm25 		\n"

		"   vbroadcastss	32(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm26 		\n"

		"	addq 			$64, %%rbx  					\n"

		"   vbroadcastss	36(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm27 		\n"

		"   prefetcht0 		64(%%rbx)                 		\n"

		"   vbroadcastss	40(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm28 		\n"

		"   vbroadcastss	44(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm29 		\n"
		"   vmovups 		(%%rbx), %%zmm4        			\n" 
		"	addq  			$48, %%rax 						\n"

		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm30 		\n"

		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm31 		\n"

		".endm 												\n"



		".macro	KERNEL12x16_END_K							\n"


		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm20 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"	
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm21 		\n"

		"   vbroadcastss	16(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm22 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	20(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm23 		\n"

		"   vbroadcastss	24(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm24 		\n"

		"   vbroadcastss	28(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm25 		\n"

		"   vbroadcastss	32(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm26 		\n"

		"   vbroadcastss	36(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm27 		\n"

		"   vbroadcastss	40(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm28 		\n"

		"   vbroadcastss	44(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm29 		\n"
		"   vmovups 		(%%rbx), %%zmm4        			\n" 
		"	addq  			$48, %%rax 						\n"

		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm30 		\n"

		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm31 		\n"

		".endm 												\n"


		".macro	ADD_C_12x16									\n"


		"   vmovups 		(%%r10), %%zmm0        			\n"
		"	vaddps 			%%zmm0, %%zmm20, %%zmm20		\n"
		"   vmovups 		(%%r11), %%zmm1        			\n"
		"	vaddps 			%%zmm1, %%zmm21, %%zmm21		\n"
		"   vmovups 		(%%r12), %%zmm2        			\n"
		"	vaddps 			%%zmm2, %%zmm22, %%zmm22		\n"
		"   vmovups 		(%%r13), %%zmm3        			\n"
		"	vaddps 			%%zmm3, %%zmm23, %%zmm23		\n"

		"	leaq  			(%%r13, %%r8, 4), %%r10 		\n"  // C0
		"	leaq 			(%%r10, %%r8, 4), %%r11 		\n"	 // C1
		"	leaq 			(%%r11, %%r8, 4), %%r12 		\n"  // C2
		"	leaq 			(%%r12, %%r8, 4), %%r13 		\n"  // C3

		"   vmovups 		(%%r10), %%zmm4        			\n"
		"	vaddps 			%%zmm4, %%zmm24, %%zmm24		\n"
		"   vmovups 		(%%r11), %%zmm5        			\n"
		"	vaddps 			%%zmm5, %%zmm25, %%zmm25		\n"
		"   vmovups 		(%%r12), %%zmm6        			\n"
		"	vaddps 			%%zmm6, %%zmm26, %%zmm26		\n"
		"   vmovups 		(%%r13), %%zmm7        			\n"
		"	vaddps 			%%zmm7, %%zmm27, %%zmm27		\n"

		"	leaq  			(%%r13, %%r8, 4), %%r10 		\n"  // C0
		"	leaq 			(%%r10, %%r8, 4), %%r11 		\n"	 // C1
		"	leaq 			(%%r11, %%r8, 4), %%r12 		\n"  // C2
		"	leaq 			(%%r12, %%r8, 4), %%r13 		\n"  // C3


		"   vmovups 		(%%r10), %%zmm0        			\n"
		"	vaddps 			%%zmm0, %%zmm28, %%zmm28		\n"
		"   vmovups 		(%%r11), %%zmm1        			\n"
		"	vaddps 			%%zmm1, %%zmm29, %%zmm29		\n"
		"   vmovups 		(%%r12), %%zmm2        			\n"
		"	vaddps 			%%zmm2, %%zmm30, %%zmm30		\n"
		"   vmovups 		(%%r13), %%zmm3        			\n"
		"	vaddps 			%%zmm3, %%zmm31, %%zmm31		\n"


		"	mov  	%%rcx, %%r10 							\n"  // C0
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3


		".endm 												\n"



		".macro	SAVE_12x16 									\n"

		"   vmovups 		%%zmm20, (%%r10)        		\n"
		"   vmovups 		%%zmm21, (%%r11)        		\n"
		"	subq 			$12, %%rdi 						\n"
		"   vmovups 		%%zmm22, (%%r12)        		\n"
		"   vmovups 		%%zmm23, (%%r13)        		\n" 

		"	leaq  	(%%r13, %%r8, 4), %%r10 				\n"  // C0
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3

		"   vmovups 		%%zmm24, (%%r10)        		\n"
		"   vmovups 		%%zmm25, (%%r11)        		\n"
		"   vmovups 		%%zmm26, (%%r12)        		\n"
		"   vmovups 		%%zmm27, (%%r13)        		\n"

		"	leaq  	(%%r13, %%r8, 4), %%r10 				\n"  // C0
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3

		"   vmovups 		%%zmm28, (%%r10)        		\n"
		"   vmovups 		%%zmm29, (%%r11)        		\n"
		"   vmovups 		%%zmm30, (%%r12)        		\n"
		"   vmovups 		%%zmm31, (%%r13)        		\n"

		"	leaq  	(%%r13, %%r8, 4), %%rcx 				\n"  // C0


		".endm 												\n"


//-----------------------------------------------------------------------

		".macro	KERNEL8x16_K1								\n"

		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm4, %%zmm24 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm4, %%zmm25 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	16(%%rax), %%zmm8    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm4, %%zmm26 		\n"

		"   vbroadcastss	20(%%rax), %%zmm9    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm4, %%zmm27 		\n"

		"   vbroadcastss	24(%%rax), %%zmm10    			\n"
		"   vfmadd231ps		%%zmm8, %%zmm4, %%zmm28 		\n"

		"   prefetcht0 		64(%%rbx)                 		\n"

		"   vbroadcastss	28(%%rax), %%zmm11    			\n"
		"   vfmadd231ps		%%zmm9, %%zmm4, %%zmm29 		\n"
		"	addq  			$64, %%rbx 						\n"  //B
		"   vfmadd231ps		%%zmm10, %%zmm4, %%zmm30 		\n"

		"	addq  			$32, %%rax 						\n"
		"   vmovups 		(%%rbx), %%zmm6        			\n" 
		"   vfmadd231ps		%%zmm11, %%zmm4, %%zmm31 		\n"

		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vbroadcastss	4(%%rax), %%zmm1    			\n"

		
		".endm 												\n"


		".macro	KERNEL8x16_K2								\n"

		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm24 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm25 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	16(%%rax), %%zmm8    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm26 		\n"

		"   vbroadcastss	20(%%rax), %%zmm9    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm27 		\n"

		"   vbroadcastss	24(%%rax), %%zmm10    			\n"
		"   vfmadd231ps		%%zmm8, %%zmm6, %%zmm28 		\n"

		"   prefetcht0 		64(%%rbx)                 		\n"

		"   vbroadcastss	28(%%rax), %%zmm11    			\n"
		"   vfmadd231ps		%%zmm9, %%zmm6, %%zmm29 		\n"
		"	addq  			$64, %%rbx 						\n"  //B
		"   vfmadd231ps		%%zmm10, %%zmm6, %%zmm30 		\n"

		"	addq  			$32, %%rax 						\n"
		"   vmovups 		(%%rbx), %%zmm4        			\n" 
		"   vfmadd231ps		%%zmm11, %%zmm6, %%zmm31 		\n"
		
		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vbroadcastss	4(%%rax), %%zmm1    			\n"

		".endm 												\n"



		".macro	KERNEL8x16_END_K							\n"


		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm24 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm25 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	16(%%rax), %%zmm8    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm26 		\n"

		"   vbroadcastss	20(%%rax), %%zmm9    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm27 		\n"

		"   vbroadcastss	24(%%rax), %%zmm10    			\n"
		"   vfmadd231ps		%%zmm8, %%zmm6, %%zmm28 		\n"

		"   vbroadcastss	28(%%rax), %%zmm11    			\n"
		"   vfmadd231ps		%%zmm9, %%zmm6, %%zmm29 		\n"
		"   vfmadd231ps		%%zmm10, %%zmm6, %%zmm30 		\n"

		"	addq  			$32, %%rax 						\n"
		"   vfmadd231ps		%%zmm11, %%zmm6, %%zmm31 		\n"

		".endm 												\n"


		".macro	ADD_C_8x16									\n"


		"   vmovups 		(%%r10), %%zmm4        			\n"
		"	vaddps 			%%zmm4, %%zmm24, %%zmm24		\n"
		"   vmovups 		(%%r11), %%zmm5        			\n"
		"	vaddps 			%%zmm5, %%zmm25, %%zmm25		\n"
		"   vmovups 		(%%r12), %%zmm6        			\n"
		"	vaddps 			%%zmm6, %%zmm26, %%zmm26		\n"
		"   vmovups 		(%%r13), %%zmm7        			\n"
		"	vaddps 			%%zmm7, %%zmm27, %%zmm27		\n"

		"	leaq  			(%%r13, %%r8, 4), %%r10 		\n"  // C0
		"	leaq 			(%%r10, %%r8, 4), %%r11 		\n"	 // C1
		"	leaq 			(%%r11, %%r8, 4), %%r12 		\n"  // C2
		"	leaq 			(%%r12, %%r8, 4), %%r13 		\n"  // C3


		"   vmovups 		(%%r10), %%zmm0        			\n"
		"	vaddps 			%%zmm0, %%zmm28, %%zmm28		\n"
		"   vmovups 		(%%r11), %%zmm1        			\n"
		"	vaddps 			%%zmm1, %%zmm29, %%zmm29		\n"
		"   vmovups 		(%%r12), %%zmm2        			\n"
		"	vaddps 			%%zmm2, %%zmm30, %%zmm30		\n"
		"   vmovups 		(%%r13), %%zmm3        			\n"
		"	vaddps 			%%zmm3, %%zmm31, %%zmm31		\n"


		"	mov  	%%rcx, %%r10 							\n"  // C0
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3


		".endm 												\n"



		".macro	SAVE_8x16 									\n"

		"   vmovups 		%%zmm24, (%%r10)        		\n"
		"   vmovups 		%%zmm25, (%%r11)        		\n"
		"	subq 			$8, %%rdi 						\n"
		"   vmovups 		%%zmm26, (%%r12)        		\n"
		"   vmovups 		%%zmm27, (%%r13)        		\n"

		"	leaq  	(%%r13, %%r8, 4), %%r10 				\n"  // C0
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3

		"   vmovups 		%%zmm28, (%%r10)        		\n"
		"   vmovups 		%%zmm29, (%%r11)        		\n"
		"   vmovups 		%%zmm30, (%%r12)        		\n"
		"   vmovups 		%%zmm31, (%%r13)        		\n"

		"	leaq  	(%%r13, %%r8, 4), %%rcx 				\n"  // C0


		".endm 												\n"


//-----------------------------------------------------------------------

		".macro	KERNEL4x16_K1								\n"

		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm4, %%zmm28 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm4, %%zmm29 		\n"
		"	addq  			$16, %%rax 						\n"

		"   prefetcht0 		256(%%rax)                 		\n"
		"	addq  			$64, %%rbx 						\n"  //B
		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vfmadd231ps		%%zmm2, %%zmm4, %%zmm30 		\n"

		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm4, %%zmm31 		\n"

		"   prefetcht0 		64(%%rbx)                 		\n"
		"   vmovups 		(%%rbx), %%zmm6        			\n" 

		".endm 												\n"


		".macro	KERNEL4x16_K2								\n"

		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm28 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm29 		\n"
		"	addq  			$16, %%rax 						\n"

		"   prefetcht0 		256(%%rax)                 		\n"
		"	addq  			$64, %%rbx 						\n"  //B
		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm30 		\n"

		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm31 		\n"

		"   vmovups 		(%%rbx), %%zmm4        			\n" 
		"   prefetcht0 		64(%%rbx)                 		\n"
		
		".endm 												\n"



		".macro	KERNEL4x16_END_K							\n"

		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm28 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm29 		\n"
		"	addq  			$16, %%rax 						\n"

		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm30 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm31 		\n"

		".endm 												\n"


		".macro	ADD_C_4x16									\n"

		"   vmovups 		(%%r10), %%zmm0        			\n"
		"	vaddps 			%%zmm0, %%zmm28, %%zmm28		\n"
		"   vmovups 		(%%r11), %%zmm1        			\n"
		"	vaddps 			%%zmm1, %%zmm29, %%zmm29		\n"
		"   vmovups 		(%%r12), %%zmm2        			\n"
		"	vaddps 			%%zmm2, %%zmm30, %%zmm30		\n"
		"   vmovups 		(%%r13), %%zmm3        			\n"
		"	vaddps 			%%zmm3, %%zmm31, %%zmm31		\n"


		"	mov  	%%rcx, %%r10 							\n"  // C0
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3


		".endm 												\n"



		".macro	SAVE_4x16 									\n"

		"   vmovups 		%%zmm28, (%%r10)        		\n"
		"   vmovups 		%%zmm29, (%%r11)        		\n"
		"   vmovups 		%%zmm30, (%%r12)        		\n"
		"   vmovups 		%%zmm31, (%%r13)        		\n"

		"	leaq  	(%%r13, %%r8, 4), %%rcx 				\n"  // C0


		".endm 												\n"


//-----------------------------------------------------------------
		"SMM_NN_KERNEL12x16:								\n"

		"   mov 	%[C], %%rcx   	 						\n"
		"   mov 	%[A], %%rax   	 						\n"
		"   mov 	%[B], %%rbx   	 						\n"

		"   prefetcht0 		(%%rax)                 		\n"

		"	mov 	%[K], %%rdx 							\n"  // K
		"	mov  	%[LN], %%r8 							\n" 
		"	mov  	%[Bc], %%r14 							\n"
		"	mov  	%[M], %%rdi 							\n"
		"	mov 	%[k_tag], %%r15 						\n"

		"   prefetcht0 		(%%rbx)                 		\n"
		"	mov 	%%rbx, %%r9 							\n"  // 
		"	mov 	%%rdx, %%rsi 							\n"  // K



		"BEGIN_PACK12x16:									\n"

		"	mov 	%%r9, %%rbx 							\n"  // B
		"   prefetcht0 		(%%rbx)                 		\n" 

		"	mov  	%%rcx, %%r10 							\n"  // C0
		"   prefetcht1 		(%%r10)                 		\n"
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"   prefetcht1 		(%%r11)                 		\n"
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"   prefetcht1 		(%%r12)                 		\n"
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3
		"   prefetcht1 		(%%r13)                 		\n"

		"	mov 	%%rsi, %%rdx 							\n"  // K
		"	mov 	%%r14, %%rbp 							\n"  // Bc

		"   vmovups		(%%rbx), %%zmm4        				\n"
		"	vpxorq 		%%zmm20, %%zmm20, %%zmm20 			\n"
		"	vpxorq 		%%zmm21, %%zmm21, %%zmm21 			\n"
		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"	vpxorq 		%%zmm22, %%zmm22, %%zmm22 			\n" 
		"	vpxorq 		%%zmm23, %%zmm23, %%zmm23 			\n"
		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"	vpxorq 		%%zmm24, %%zmm24, %%zmm24 			\n"
		"	vpxorq 		%%zmm25, %%zmm25, %%zmm25			\n"
		"	vpxorq 		%%zmm26, %%zmm26, %%zmm26 			\n" 
		"	vpxorq 		%%zmm27, %%zmm27, %%zmm27 			\n"
		"	vpxorq 		%%zmm28, %%zmm28, %%zmm28 			\n"
		"	vpxorq 		%%zmm29, %%zmm29, %%zmm29			\n" 
		"	vpxorq 		%%zmm30, %%zmm30, %%zmm30 			\n" 
		"	vpxorq 		%%zmm31, %%zmm31, %%zmm31 			\n"   

		"	subq 	$8, %%rdx 								\n"

		"MAIN_PACK_K12x16:									\n"


		"	KERNEL12x16_PACK_K1 							\n"
		"	KERNEL12x16_PACK_K2 							\n"
		"	KERNEL12x16_PACK_K1 							\n"
		"	KERNEL12x16_PACK_K2 							\n"
		"	KERNEL12x16_PACK_K1 							\n"
		"	KERNEL12x16_PACK_K2 							\n"
		"	KERNEL12x16_PACK_K1 							\n"
		"   cmp 	$0, %%rdx           					\n"
		"	je 		EDGE_PACK_K12x16 						\n"
		"	KERNEL12x16_PACK_K2 							\n"

		"	subq 	$8, %%rdx 								\n"
		"   jmp     MAIN_PACK_K12x16       					\n"
		

		"EDGE_PACK_K12x16:									\n"

		"	KERNEL12x16_PACK_END_K 							\n"
		"	jmp  	BEGIN_SAVE_12x16 						\n"
		
//-----------------------------------------------------------------

		"BEGIN_M12x16:										\n"

		"	mov 	%%r14, %%rbx 							\n"  // Bc
		"   prefetcht0 		(%%rbx)                 		\n" 

		"	mov  	%%rcx, %%r10 							\n"  // C0
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3

		"	mov 	%%rsi, %%rdx 							\n"  // K

		"BEGIN_K12x16:										\n"

		"   vmovups		(%%rbx), %%zmm4        				\n"
		"	vpxorq 		%%zmm20, %%zmm20, %%zmm20 			\n"
		"	vpxorq 		%%zmm21, %%zmm21, %%zmm21 			\n" 
		"	vpxorq 		%%zmm22, %%zmm22, %%zmm22 			\n"
		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"	vpxorq 		%%zmm23, %%zmm23, %%zmm23 			\n"
		"	vpxorq 		%%zmm24, %%zmm24, %%zmm24 			\n"
		"   vbroadcastss	4(%%rax), %%zmm1    			\n" 
		"	vpxorq 		%%zmm25, %%zmm25, %%zmm25			\n" 
		"	vpxorq 		%%zmm26, %%zmm26, %%zmm26 			\n" 
		"	vpxorq 		%%zmm27, %%zmm27, %%zmm27 			\n"
		"	vpxorq 		%%zmm28, %%zmm28, %%zmm28 			\n"
		"	vpxorq 		%%zmm29, %%zmm29, %%zmm29			\n" 
		"	vpxorq 		%%zmm30, %%zmm30, %%zmm30 			\n" 
		"	vpxorq 		%%zmm31, %%zmm31, %%zmm31 			\n"   

		"	subq 	$8, %%rdx 								\n"

		"MAIN_K12x16:										\n"


		"	KERNEL12x16_K1 									\n"
		"	KERNEL12x16_K2 									\n"
		"	KERNEL12x16_K1 									\n"
		"	KERNEL12x16_K2 									\n"
		"	KERNEL12x16_K1 									\n"
		"	KERNEL12x16_K2 									\n"
		"	KERNEL12x16_K1 									\n"
		"   cmp 	$0, %%rdx           					\n"
		"	je 		EDGE_K12x16 							\n"
		"	KERNEL12x16_K2 									\n"

		"	subq 	$8, %%rdx 								\n"
		"   jmp     MAIN_K12x16       						\n"
		

		"EDGE_K12x16:										\n"

		"	KERNEL12x16_END_K 								\n"


		"BEGIN_SAVE_12x16:									\n"
		"	cmp 	$0, %%r15								\n"
		"	je  	SAVE_C12x16 							\n"
		"	ADD_C_12x16 									\n"
		"SAVE_C12x16: 										\n"
		"	SAVE_12x16 										\n"

		"	cmpq  	$12, %%rdi 								\n"
		"	jnb 	BEGIN_M12x16 							\n"


//------------------------------------------------------------------
//------------------------------------------------------------------
		"EDGE_M_N16:										\n"
		"	cmpq  	$8, %%rdi  								\n"   //M % 12
		"	jb   	BEGIN_M4_N16 							\n"


		"BEGIN_M8_N16:										\n"

		"	mov 	%%r14, %%rbx 							\n"  // Bc
		"   prefetcht0 		(%%rbx)                 		\n" 

		"	mov  	%%rcx, %%r10 							\n"  // C0
		"   prefetcht1 		(%%r10)                 		\n"
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"   prefetcht1 		(%%r11)                 		\n"
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"   prefetcht1 		(%%r12)                 		\n"
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3
		"   prefetcht1 		(%%r13)                 		\n"

		"	mov 	%%rsi, %%rdx 							\n"  // K
		"   vmovups		(%%rbx), %%zmm4        				\n"
		"	vpxorq 		%%zmm24, %%zmm24, %%zmm24 			\n"
		"	vpxorq 		%%zmm25, %%zmm25, %%zmm25			\n"
		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"	vpxorq 		%%zmm26, %%zmm26, %%zmm26 			\n" 
		"	vpxorq 		%%zmm27, %%zmm27, %%zmm27 			\n"
		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"	vpxorq 		%%zmm28, %%zmm28, %%zmm28 			\n"
		"	vpxorq 		%%zmm29, %%zmm29, %%zmm29			\n" 
		"	vpxorq 		%%zmm30, %%zmm30, %%zmm30 			\n" 
		"	vpxorq 		%%zmm31, %%zmm31, %%zmm31 			\n"   

		"	subq 	$8, %%rdx 								\n"

		"MAIN_K_M8_N16:										\n"

		"	KERNEL8x16_K1 									\n"
		"	KERNEL8x16_K2 									\n"
		"	KERNEL8x16_K1 									\n"
		"	KERNEL8x16_K2 									\n"
		"	KERNEL8x16_K1 									\n"
		"	KERNEL8x16_K2 									\n"
		"	KERNEL8x16_K1 									\n"
		"   cmp 	$0, %%rdx           					\n"
		"	je 		EDGE_K_M8_N16 							\n"
		"	KERNEL8x16_K2 									\n"

		"	subq 	$8, %%rdx 								\n"
		"   jmp     MAIN_K_M8_N16       					\n"
		

		"EDGE_K_M8_N16:										\n"

		"	KERNEL8x16_END_K 								\n"

		"	cmp 	$0, %%r15								\n"
		"	je  	SAVE_C_8x16 							\n"
		"	ADD_C_8x16 										\n"
		"SAVE_C_8x16: 										\n"
		"	SAVE_8x16 										\n"


//----------------------------------------------------------------
		"BEGIN_M4_N16:										\n"

		"	cmpq  	$4, %%rdi  								\n"   //M % 12
		"	jb   	END_M_N16 								\n"

		"	mov 	%%r14, %%rbx 							\n"  // Bc
		"   prefetcht0 		(%%rbx)                 		\n" 

		"	mov  	%%rcx, %%r10 							\n"  // C0
		"   prefetcht1 		(%%r10)                 		\n"
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"   prefetcht1 		(%%r11)                 		\n"
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"   prefetcht1 		(%%r12)                 		\n"
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3
		"   prefetcht1 		(%%r13)                 		\n"

		"	mov 	%%rsi, %%rdx 							\n"  // K

		"   vmovups		(%%rbx), %%zmm4        				\n"
		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"	vpxorq 		%%zmm28, %%zmm28, %%zmm28 			\n"
		"	vpxorq 		%%zmm29, %%zmm29, %%zmm29			\n"
		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"	vpxorq 		%%zmm30, %%zmm30, %%zmm30 			\n" 
		"	vpxorq 		%%zmm31, %%zmm31, %%zmm31 			\n"   

		"	subq 	$8, %%rdx 								\n"

		"MAIN_K_M4_N16:										\n"


		"	KERNEL4x16_K1 									\n"
		"	KERNEL4x16_K2 									\n"
		"	KERNEL4x16_K1 									\n"
		"	KERNEL4x16_K2 									\n"
		"	KERNEL4x16_K1 									\n"
		"	KERNEL4x16_K2 									\n"
		"	KERNEL4x16_K1 									\n"
		"   cmp 	$0, %%rdx           					\n"
		"	je 		EDGE_K_M4_N16 							\n"
		"	KERNEL4x16_K2 									\n"

		"	subq 	$8, %%rdx 								\n"
		"   jmp     MAIN_K_M4_N16       					\n"
		

		"EDGE_K_M4_N16:										\n"

		"	KERNEL4x16_END_K 								\n"

		"	cmp 	$0, %%r15								\n"
		"	je  	SAVE_C_4x16 							\n"
		"	ADD_C_4x16 										\n"
		"SAVE_C_4x16: 										\n"
		"	SAVE_4x16 										\n"

		"END_M_N16:											\n"


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
		 [Bc] "m" (Bc),
		 [k_tag] "m" (k_tag)   
		:
		 "rax", "rbx", "rcx", "rdx", "rdi", "rsi","rbp","r8", "r9", "r10", "r11", "r12",
		 "r13", "r14", "r15", "zmm0", "zmm1", "zmm2", "zmm3", "zmm4", "zmm5",
		 "zmm6", "zmm7", "zmm8", "zmm9", "zmm10", "zmm11", "zmm12", "zmm13",
		 "zmm14", "zmm15", "zmm16", "zmm17", "zmm18", "zmm19", "zmm20", "zmm21",
		 "zmm22", "zmm23", "zmm24", "zmm25", "zmm26", "zmm27", "zmm28", "zmm29",
		 "zmm30", "zmm31", "memory"
    
    );

}



void SMM_NN_KERNEL12x32(float *C, float *A, float *B, long M, 
						long N, long K, long LN, long LK, float *Bc, long k_tag)
{

	asm volatile(


		".macro	KERNEL12x32_PACK_K1							\n"

		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm4, %%zmm8 			\n"
		"   vfmadd231ps		%%zmm0, %%zmm5, %%zmm9 			\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm4, %%zmm10 		\n"
		"   vfmadd231ps		%%zmm1, %%zmm5, %%zmm11 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	16(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm4, %%zmm12 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm5, %%zmm13 		\n"

		"   prefetcht2 		128(%%rbx)                 		\n"

		"   vbroadcastss	20(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm4, %%zmm14 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm5, %%zmm15 		\n"

		"   vbroadcastss	24(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm4, %%zmm16 		\n"
		"   vfmadd231ps		%%zmm0, %%zmm5, %%zmm17 		\n"

		"   prefetcht2 		192(%%rbx)                 		\n"

		"   vbroadcastss	28(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm4, %%zmm18 		\n"
		"   vfmadd231ps		%%zmm1, %%zmm5, %%zmm19 		\n"

		"   vbroadcastss	32(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm4, %%zmm20 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm5, %%zmm21 		\n"

		"	leaq  	(%%rbx, %%r8, 4), %%rbx 				\n"  // B

		"   vbroadcastss	36(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm4, %%zmm22 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm5, %%zmm23 		\n"

		"   vbroadcastss	40(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm4, %%zmm24 		\n"
		"   vfmadd231ps		%%zmm0, %%zmm5, %%zmm25 		\n"

		"   prefetcht0 		384(%%rax)                 		\n"

		"   vbroadcastss	44(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm4, %%zmm26 		\n"
		"   vmovups 		(%%rbx), %%zmm6        			\n" 
		"	addq  			$48, %%rax 						\n"
		"   vfmadd231ps		%%zmm1, %%zmm5, %%zmm27 		\n"

		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vfmadd231ps		%%zmm2, %%zmm4, %%zmm28 		\n"
		"   vmovups 		64(%%rbx), %%zmm7       		\n"
		"   vfmadd231ps		%%zmm2, %%zmm5, %%zmm29 		\n"

		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm4, %%zmm30 		\n"
		"   vmovups 		%%zmm4, (%%rbp)       			\n"
		"   vfmadd231ps		%%zmm3, %%zmm5, %%zmm31 		\n"
		"   vmovups 		%%zmm5, 64(%%rbp)       		\n"
		"	addq  			$128, %%rbp 					\n"

		

		".endm 												\n"


		".macro	KERNEL12x32_PACK_K2							\n"

		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm8 			\n"
		"   vfmadd231ps		%%zmm0, %%zmm7, %%zmm9 			\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm10 		\n"
		"   vfmadd231ps		%%zmm1, %%zmm7, %%zmm11 		\n"

		"   prefetcht2 		128(%%rbx)                 		\n"

		"   vbroadcastss	16(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm12 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm7, %%zmm13 		\n"

		"   prefetcht2 		192(%%rbx)                 		\n"

		"   vbroadcastss	20(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm14 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm7, %%zmm15 		\n"

		"   vbroadcastss	24(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm16 		\n"
		"   vfmadd231ps		%%zmm0, %%zmm7, %%zmm17 		\n"

		"   vbroadcastss	28(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm18 		\n"
		"   vfmadd231ps		%%zmm1, %%zmm7, %%zmm19 		\n"

		"   vbroadcastss	32(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm20 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm7, %%zmm21 		\n"

		"	leaq  	(%%rbx, %%r8, 4), %%rbx 				\n"  // B

		"   vbroadcastss	36(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm22 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm7, %%zmm23 		\n"

		"   vbroadcastss	40(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm24 		\n"
		"   vfmadd231ps		%%zmm0, %%zmm7, %%zmm25 		\n"

		"   vbroadcastss	44(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm26 		\n"
		"   vmovups 		(%%rbx), %%zmm4        			\n" 
		"	addq  			$48, %%rax 						\n"
		"   vfmadd231ps		%%zmm1, %%zmm7, %%zmm27 		\n"

		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm28 		\n"
		"   vmovups 		64(%%rbx), %%zmm5       		\n"
		"   vfmadd231ps		%%zmm2, %%zmm7, %%zmm29 		\n"

		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm30 		\n"
		"   vmovups 		%%zmm6, (%%rbp)       			\n"
		"   vfmadd231ps		%%zmm3, %%zmm7, %%zmm31 		\n"
		"   vmovups 		%%zmm7, 64(%%rbp)       		\n"
		"	addq  			$128, %%rbp 					\n"


		".endm 												\n"



		".macro	KERNEL12x32_PACK_END_K						\n"


		"   vbroadcastss	8(%%rax), %%zmm2    			\n"

		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm8 			\n"
		"   vfmadd231ps		%%zmm0, %%zmm7, %%zmm9 			\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm10 		\n"
		"   vfmadd231ps		%%zmm1, %%zmm7, %%zmm11 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	16(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm12 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm7, %%zmm13 		\n"

		"   vbroadcastss	20(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm14 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm7, %%zmm15 		\n"

		"   vbroadcastss	24(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm16 		\n"
		"   vfmadd231ps		%%zmm0, %%zmm7, %%zmm17 		\n"

		"   vbroadcastss	28(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm18 		\n"
		"   vfmadd231ps		%%zmm1, %%zmm7, %%zmm19 		\n"

		"   vbroadcastss	32(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm20 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm7, %%zmm21 		\n"

		"   vbroadcastss	36(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm22 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm7, %%zmm23 		\n"

		"   vbroadcastss	40(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm24 		\n"
		"   vfmadd231ps		%%zmm0, %%zmm7, %%zmm25 		\n"

		"   vbroadcastss	44(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm26 		\n"
		"	addq  			$48, %%rax 						\n"
		"   vfmadd231ps		%%zmm1, %%zmm7, %%zmm27 		\n"

		"   vmovups 		%%zmm6, (%%rbp)       			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm28 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm7, %%zmm29 		\n"

		"   vmovups 		%%zmm7, 64(%%rbp)       		\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm30 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm7, %%zmm31 		\n"


		".endm 												\n"



		".macro	KERNEL12x32_K1								\n"

		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm4, %%zmm8 			\n"
		"   vfmadd231ps		%%zmm0, %%zmm5, %%zmm9 			\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		
		"   vfmadd231ps		%%zmm1, %%zmm4, %%zmm10 		\n"
		"   vfmadd231ps		%%zmm1, %%zmm5, %%zmm11 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	16(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm4, %%zmm12 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm5, %%zmm13 		\n"

		"   vbroadcastss	20(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm4, %%zmm14 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm5, %%zmm15 		\n"

		"   vbroadcastss	24(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm4, %%zmm16 		\n"
		"   vfmadd231ps		%%zmm0, %%zmm5, %%zmm17 		\n"

		"   vbroadcastss	28(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm4, %%zmm18 		\n"
		"   vfmadd231ps		%%zmm1, %%zmm5, %%zmm19 		\n"

		"   vbroadcastss	32(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm4, %%zmm20 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm5, %%zmm21 		\n"

		"	addq  			$128, %%rbx 					\n"

		"   vbroadcastss	36(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm4, %%zmm22 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm5, %%zmm23 		\n"

		"   prefetcht0 		64(%%rbx)                 		\n"

		"   vbroadcastss	40(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm4, %%zmm24 		\n"
		"   vfmadd231ps		%%zmm0, %%zmm5, %%zmm25 		\n"

		"   vbroadcastss	44(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm4, %%zmm26 		\n"
		"   vmovups 		(%%rbx), %%zmm6        			\n" 
		"	addq  			$48, %%rax 						\n"
		"   vfmadd231ps		%%zmm1, %%zmm5, %%zmm27 		\n"

		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vfmadd231ps		%%zmm2, %%zmm4, %%zmm28 		\n"
		"   vmovups 		64(%%rbx), %%zmm7       		\n"
		"   vfmadd231ps		%%zmm2, %%zmm5, %%zmm29 		\n"

		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm4, %%zmm30 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm5, %%zmm31 		\n"

		

		".endm 												\n"


		".macro	KERNEL12x32_K2								\n"

		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm8 			\n"
		"   vfmadd231ps		%%zmm0, %%zmm7, %%zmm9 			\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm10 		\n"
		"   vfmadd231ps		%%zmm1, %%zmm7, %%zmm11 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	16(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm12 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm7, %%zmm13 		\n"

		"   vbroadcastss	20(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm14 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm7, %%zmm15 		\n"

		"   vbroadcastss	24(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm16 		\n"
		"   vfmadd231ps		%%zmm0, %%zmm7, %%zmm17 		\n"

		"   vbroadcastss	28(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm18 		\n"
		"   vfmadd231ps		%%zmm1, %%zmm7, %%zmm19 		\n"

		"   vbroadcastss	32(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm20 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm7, %%zmm21 		\n"

		"	addq  			$128, %%rbx 					\n"

		"   vbroadcastss	36(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm22 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm7, %%zmm23 		\n"

		"   prefetcht0 		64(%%rbx)                 		\n"

		"   vbroadcastss	40(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm24 		\n"
		"   vfmadd231ps		%%zmm0, %%zmm7, %%zmm25 		\n"

		"   vbroadcastss	44(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm26 		\n"
		"   vmovups 		(%%rbx), %%zmm4        			\n" 
		"	addq  			$48, %%rax 						\n"
		"   vfmadd231ps		%%zmm1, %%zmm7, %%zmm27 		\n"

		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm28 		\n"
		"   vmovups 		64(%%rbx), %%zmm5       		\n"
		"   vfmadd231ps		%%zmm2, %%zmm7, %%zmm29 		\n"

		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm30 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm7, %%zmm31 		\n"


		".endm 												\n"



		".macro	KERNEL12x32_END_K							\n"


		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm8 			\n"
		"   vfmadd231ps		%%zmm0, %%zmm7, %%zmm9 			\n"
		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm10 		\n"
		"   vfmadd231ps		%%zmm1, %%zmm7, %%zmm11 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	16(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm12 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm7, %%zmm13 		\n"

		"   vbroadcastss	20(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm14 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm7, %%zmm15 		\n"

		"   vbroadcastss	24(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm16 		\n"
		"   vfmadd231ps		%%zmm0, %%zmm7, %%zmm17 		\n"

		"   vbroadcastss	28(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm18 		\n"
		"   vfmadd231ps		%%zmm1, %%zmm7, %%zmm19 		\n"

		"   vbroadcastss	32(%%rax), %%zmm0    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm20 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm7, %%zmm21 		\n"

		"   vbroadcastss	36(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm22 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm7, %%zmm23 		\n"

		"   vbroadcastss	40(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm24 		\n"
		"   vfmadd231ps		%%zmm0, %%zmm7, %%zmm25 		\n"

		"   vbroadcastss	44(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm26 		\n"
		"	addq  			$48, %%rax 						\n"
		"   vfmadd231ps		%%zmm1, %%zmm7, %%zmm27 		\n"

		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm28 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm7, %%zmm29 		\n"

		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm30 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm7, %%zmm31 		\n"


		".endm 												\n"


		".macro	ADD_C_12x32									\n"

		"   vmovups 		(%%r10), %%zmm0        			\n"
		"	vaddps 			%%zmm0, %%zmm8, %%zmm8			\n"
		"   vmovups 		64(%%r10), %%zmm1        		\n"
		"	vaddps 			%%zmm1, %%zmm9, %%zmm9			\n"
		"   vmovups 		(%%r11), %%zmm2        			\n"
		"	vaddps 			%%zmm2, %%zmm10, %%zmm10		\n"
		"   vmovups 		64(%%r11), %%zmm3        		\n"
		"	vaddps 			%%zmm3, %%zmm11, %%zmm11		\n"
		"   vmovups 		(%%r12), %%zmm4        			\n"
		"	vaddps 			%%zmm4, %%zmm12, %%zmm12		\n"
		"   vmovups 		64(%%r12), %%zmm5        		\n"
		"	vaddps 			%%zmm5, %%zmm13, %%zmm13		\n"
		"   vmovups 		(%%r13), %%zmm6        			\n"
		"	vaddps 			%%zmm6, %%zmm14, %%zmm14		\n"
		"   vmovups 		64(%%r13), %%zmm7        		\n"
		"	vaddps 			%%zmm7, %%zmm15, %%zmm15		\n"

		"	leaq  			(%%r13, %%r8, 4), %%r10 		\n"  // C0
		"	leaq 			(%%r10, %%r8, 4), %%r11 		\n"	 // C1
		"	leaq 			(%%r11, %%r8, 4), %%r12 		\n"  // C2
		"	leaq 			(%%r12, %%r8, 4), %%r13 		\n"  // C3

		"   vmovups 		(%%r10), %%zmm0        			\n"
		"	vaddps 			%%zmm0, %%zmm16, %%zmm16		\n"
		"   vmovups 		64(%%r10), %%zmm1        		\n"
		"	vaddps 			%%zmm1, %%zmm17, %%zmm17		\n"
		"   vmovups 		(%%r11), %%zmm2        			\n"
		"	vaddps 			%%zmm2, %%zmm18, %%zmm18		\n"
		"   vmovups 		64(%%r11), %%zmm3        		\n"
		"	vaddps 			%%zmm3, %%zmm19, %%zmm19		\n"

		"   vmovups 		(%%r12), %%zmm4        			\n"
		"	vaddps 			%%zmm4, %%zmm20, %%zmm20		\n"
		"   vmovups 		64(%%r12), %%zmm5        		\n"
		"	vaddps 			%%zmm5, %%zmm21, %%zmm21		\n"
		"   vmovups 		(%%r13), %%zmm6        			\n"
		"	vaddps 			%%zmm6, %%zmm22, %%zmm22		\n"
		"   vmovups 		64(%%r13), %%zmm7        		\n"
		"	vaddps 			%%zmm7, %%zmm23, %%zmm23		\n"


		"	leaq  			(%%r13, %%r8, 4), %%r10 		\n"  // C0
		"	leaq 			(%%r10, %%r8, 4), %%r11 		\n"	 // C1
		"	leaq 			(%%r11, %%r8, 4), %%r12 		\n"  // C2
		"	leaq 			(%%r12, %%r8, 4), %%r13 		\n"  // C3

		"   vmovups 		(%%r10), %%zmm0        			\n"
		"	vaddps 			%%zmm0, %%zmm24, %%zmm24		\n"
		"   vmovups 		64(%%r10), %%zmm1        		\n"
		"	vaddps 			%%zmm1, %%zmm25, %%zmm25		\n"
		"   vmovups 		(%%r11), %%zmm2        			\n"
		"	vaddps 			%%zmm2, %%zmm26, %%zmm26		\n"
		"   vmovups 		64(%%r11), %%zmm3        		\n"
		"	vaddps 			%%zmm3, %%zmm27, %%zmm27		\n"

		"   vmovups 		(%%r12), %%zmm4        			\n"
		"	vaddps 			%%zmm4, %%zmm28, %%zmm28		\n"
		"   vmovups 		64(%%r12), %%zmm5        		\n"
		"	vaddps 			%%zmm5, %%zmm29, %%zmm29		\n"
		"   vmovups 		(%%r13), %%zmm6        			\n"
		"	vaddps 			%%zmm6, %%zmm30, %%zmm30		\n"
		"   vmovups 		64(%%r13), %%zmm7        		\n"
		"	vaddps 			%%zmm7, %%zmm31, %%zmm31		\n"


		"	mov  	%%rcx, %%r10 							\n"  // C0
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3


		".endm 												\n"



		".macro	SAVE_12x32 									\n"


		"   vmovups 		%%zmm8, (%%r10)        			\n"
		"   vmovups 		%%zmm9, 64(%%r10)        		\n"
		"   vmovups 		%%zmm10, (%%r11)        		\n"
		"   vmovups 		%%zmm11, 64(%%r11)        		\n"
		"   vmovups 		%%zmm12, (%%r12)        		\n"
		"   vmovups 		%%zmm13, 64(%%r12)        		\n"
		"   vmovups 		%%zmm14, (%%r13)        		\n"
		"   vmovups 		%%zmm15, 64(%%r13)        		\n"


		"	leaq  	(%%r13, %%r8, 4), %%r10 				\n"  // C0
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3


		"   vmovups 		%%zmm16, (%%r10)        		\n"
		"   vmovups 		%%zmm17, 64(%%r10)        		\n"
		"   vmovups 		%%zmm18, (%%r11)        		\n"
		"   vmovups 		%%zmm19, 64(%%r11)        		\n"
		"   vmovups 		%%zmm20, (%%r12)        		\n"
		"   vmovups 		%%zmm21, 64(%%r12)        		\n"
		"   vmovups 		%%zmm22, (%%r13)        		\n"
		"   vmovups 		%%zmm23, 64(%%r13)        		\n" 


		"	leaq  	(%%r13, %%r8, 4), %%r10 				\n"  // C0
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3

		"   vmovups 		%%zmm24, (%%r10)        		\n"
		"   vmovups 		%%zmm25, 64(%%r10)        		\n"
		"   vmovups 		%%zmm26, (%%r11)        		\n"
		"   vmovups 		%%zmm27, 64(%%r11)        		\n"
		"	subq 			$12, %%rdi 						\n"
		"   vmovups 		%%zmm28, (%%r12)        		\n"
		"   vmovups 		%%zmm29, 64(%%r12)        		\n"
		"   vmovups 		%%zmm30, (%%r13)        		\n"
		"   vmovups 		%%zmm31, 64(%%r13)        		\n"

		"	leaq  	(%%r13, %%r8, 4), %%rcx 				\n"  // C0


		".endm 												\n"


//-----------------------------------------------------------------


		".macro	KERNEL8x32_K1								\n"

		
		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm4, %%zmm16 		\n"
		"   vfmadd231ps		%%zmm0, %%zmm5, %%zmm17 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm4, %%zmm18 		\n"
		"   vfmadd231ps		%%zmm1, %%zmm5, %%zmm19 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	16(%%rax), %%zmm8    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm4, %%zmm20 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm5, %%zmm21 		\n"

		"	addq  			$128, %%rbx 					\n"

		"   vbroadcastss	20(%%rax), %%zmm9    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm4, %%zmm22 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm5, %%zmm23 		\n"

		"   prefetcht0 		64(%%rbx)                 		\n"

		"   vbroadcastss	24(%%rax), %%zmm10    			\n"
		"   vfmadd231ps		%%zmm8, %%zmm4, %%zmm24 		\n"
		"   vfmadd231ps		%%zmm8, %%zmm5, %%zmm25 		\n"

		"   vbroadcastss	28(%%rax), %%zmm11    			\n"
		"   vfmadd231ps		%%zmm9, %%zmm4, %%zmm26 		\n"
		"   vmovups 		(%%rbx), %%zmm6        			\n" 
		"	addq  			$32, %%rax 						\n"
		"   vfmadd231ps		%%zmm9, %%zmm5, %%zmm27 		\n"

		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vfmadd231ps		%%zmm10, %%zmm4, %%zmm28 		\n"
		"   vmovups 		64(%%rbx), %%zmm7       		\n"
		"   vfmadd231ps		%%zmm10, %%zmm5, %%zmm29 		\n"

		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm11, %%zmm4, %%zmm30 		\n"
		"   vfmadd231ps		%%zmm11, %%zmm5, %%zmm31 		\n"

		".endm 												\n"



		".macro	KERNEL8x32_K2								\n"

		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm16 		\n"
		"   vfmadd231ps		%%zmm0, %%zmm7, %%zmm17 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm18 		\n"
		"   vfmadd231ps		%%zmm1, %%zmm7, %%zmm19 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	16(%%rax), %%zmm8    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm20 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm7, %%zmm21 		\n"

		"	addq  			$128, %%rbx 					\n"

		"   vbroadcastss	20(%%rax), %%zmm9    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm22 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm7, %%zmm23 		\n"

		"   prefetcht0 		64(%%rbx)                 		\n"

		"   vbroadcastss	24(%%rax), %%zmm10    			\n"
		"   vfmadd231ps		%%zmm8, %%zmm6, %%zmm24 		\n"
		"   vfmadd231ps		%%zmm8, %%zmm7, %%zmm25 		\n"

		"   vbroadcastss	28(%%rax), %%zmm11    			\n"
		"   vfmadd231ps		%%zmm9, %%zmm6, %%zmm26 		\n"
		"   vmovups 		(%%rbx), %%zmm4        			\n" 
		"	addq  			$32, %%rax 						\n"
		"   vfmadd231ps		%%zmm9, %%zmm7, %%zmm27 		\n"

		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vfmadd231ps		%%zmm10, %%zmm6, %%zmm28 		\n"
		"   vmovups 		64(%%rbx), %%zmm5       		\n"
		"   vfmadd231ps		%%zmm10, %%zmm7, %%zmm29 		\n"

		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm11, %%zmm6, %%zmm30 		\n"
		"   vfmadd231ps		%%zmm11, %%zmm7, %%zmm31 		\n"


		".endm 												\n"



		".macro	KERNEL8x32_END_K							\n"


		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm16 		\n"
		"   vfmadd231ps		%%zmm0, %%zmm7, %%zmm17 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm18 		\n"
		"   vfmadd231ps		%%zmm1, %%zmm7, %%zmm19 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	16(%%rax), %%zmm8    			\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm20 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm7, %%zmm21 		\n"

		"   vbroadcastss	20(%%rax), %%zmm9    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm6, %%zmm22 		\n"
		"   vfmadd231ps		%%zmm3, %%zmm7, %%zmm23 		\n"

		"   prefetcht0 		64(%%rbx)                 		\n"

		"   vbroadcastss	24(%%rax), %%zmm10    			\n"
		"   vfmadd231ps		%%zmm8, %%zmm6, %%zmm24 		\n"
		"   vfmadd231ps		%%zmm8, %%zmm7, %%zmm25 		\n"

		"   vbroadcastss	28(%%rax), %%zmm11    			\n"
		"   vfmadd231ps		%%zmm9, %%zmm6, %%zmm26 		\n"
		"	addq  			$32, %%rax 						\n"
		"   vfmadd231ps		%%zmm9, %%zmm7, %%zmm27 		\n"

		"   vfmadd231ps		%%zmm10, %%zmm6, %%zmm28 		\n"
		"   vfmadd231ps		%%zmm10, %%zmm7, %%zmm29 		\n"
		"   vfmadd231ps		%%zmm11, %%zmm6, %%zmm30 		\n"
		"   vfmadd231ps		%%zmm11, %%zmm7, %%zmm31 		\n"

		".endm 												\n"


		".macro	ADD_C_8x32									\n"

		"   vmovups 		(%%r10), %%zmm0        			\n"
		"	vaddps 			%%zmm0, %%zmm16, %%zmm16		\n"
		"   vmovups 		64(%%r10), %%zmm1        		\n"
		"	vaddps 			%%zmm1, %%zmm17, %%zmm17		\n"
		"   vmovups 		(%%r11), %%zmm2        			\n"
		"	vaddps 			%%zmm2, %%zmm18, %%zmm18		\n"
		"   vmovups 		64(%%r11), %%zmm3        		\n"
		"	vaddps 			%%zmm3, %%zmm19, %%zmm19		\n"

		"   vmovups 		(%%r12), %%zmm4        			\n"
		"	vaddps 			%%zmm4, %%zmm20, %%zmm20		\n"
		"   vmovups 		64(%%r12), %%zmm5        		\n"
		"	vaddps 			%%zmm5, %%zmm21, %%zmm21		\n"
		"   vmovups 		(%%r13), %%zmm6        			\n"
		"	vaddps 			%%zmm6, %%zmm22, %%zmm22		\n"
		"   vmovups 		64(%%r13), %%zmm7        		\n"
		"	vaddps 			%%zmm7, %%zmm23, %%zmm23		\n"


		"	leaq  			(%%r13, %%r8, 4), %%r10 		\n"  // C0
		"	leaq 			(%%r10, %%r8, 4), %%r11 		\n"	 // C1
		"	leaq 			(%%r11, %%r8, 4), %%r12 		\n"  // C2
		"	leaq 			(%%r12, %%r8, 4), %%r13 		\n"  // C3

		"   vmovups 		(%%r10), %%zmm0        			\n"
		"	vaddps 			%%zmm0, %%zmm24, %%zmm24		\n"
		"   vmovups 		64(%%r10), %%zmm1        		\n"
		"	vaddps 			%%zmm1, %%zmm25, %%zmm25		\n"
		"   vmovups 		(%%r11), %%zmm2        			\n"
		"	vaddps 			%%zmm2, %%zmm26, %%zmm26		\n"
		"   vmovups 		64(%%r11), %%zmm3        		\n"
		"	vaddps 			%%zmm3, %%zmm27, %%zmm27		\n"

		"   vmovups 		(%%r12), %%zmm4        			\n"
		"	vaddps 			%%zmm4, %%zmm28, %%zmm28		\n"
		"   vmovups 		64(%%r12), %%zmm5        		\n"
		"	vaddps 			%%zmm5, %%zmm29, %%zmm29		\n"
		"   vmovups 		(%%r13), %%zmm6        			\n"
		"	vaddps 			%%zmm6, %%zmm30, %%zmm30		\n"
		"   vmovups 		64(%%r13), %%zmm7        		\n"
		"	vaddps 			%%zmm7, %%zmm31, %%zmm31		\n"


		"	mov  	%%rcx, %%r10 							\n"  // C0
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3


		".endm 												\n"



		".macro	SAVE_8x32 									\n"

		"   vmovups 		%%zmm16, (%%r10)        		\n"
		"   vmovups 		%%zmm17, 64(%%r10)        		\n"
		"   vmovups 		%%zmm18, (%%r11)        		\n"
		"   vmovups 		%%zmm19, 64(%%r11)        		\n"
		"   vmovups 		%%zmm20, (%%r12)        		\n"
		"   vmovups 		%%zmm21, 64(%%r12)        		\n"
		"   vmovups 		%%zmm22, (%%r13)        		\n"
		"   vmovups 		%%zmm23, 64(%%r13)        		\n" 

		"	leaq  	(%%r13, %%r8, 4), %%r10 				\n"  // C0
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3

		"   vmovups 		%%zmm24, (%%r10)        		\n"
		"   vmovups 		%%zmm25, 64(%%r10)        		\n"
		"   vmovups 		%%zmm26, (%%r11)        		\n"
		"   vmovups 		%%zmm27, 64(%%r11)        		\n"
		"	subq 			$8, %%rdi 						\n"
		"   vmovups 		%%zmm28, (%%r12)        		\n"
		"   vmovups 		%%zmm29, 64(%%r12)        		\n"
		"   vmovups 		%%zmm30, (%%r13)        		\n"
		"   vmovups 		%%zmm31, 64(%%r13)        		\n"

		"	leaq  	(%%r13, %%r8, 4), %%rcx 				\n"  // C0


		".endm 												\n"

//---------------------------------------------------------------

		".macro	KERNEL4x32_K1								\n"
		
		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm4, %%zmm24 		\n"
		"	addq  			$128, %%rbx 					\n"
		"   vfmadd231ps		%%zmm0, %%zmm5, %%zmm25 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm4, %%zmm26 		\n"
		"	addq  			$16, %%rax 						\n"
		"   vfmadd231ps		%%zmm1, %%zmm5, %%zmm27 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vfmadd231ps		%%zmm2, %%zmm4, %%zmm28 		\n"
		"   vmovups 		(%%rbx), %%zmm6       			\n"
		"   vfmadd231ps		%%zmm2, %%zmm5, %%zmm29 		\n"

		"   vmovups 		64(%%rbx), %%zmm7       		\n"
		"   vfmadd231ps		%%zmm3, %%zmm4, %%zmm30 		\n"
		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"   vfmadd231ps		%%zmm3, %%zmm5, %%zmm31 		\n"
		"   prefetcht0 		64(%%rbx)                 		\n"

		".endm 												\n"



		".macro	KERNEL4x32_K2								\n"

		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm24 		\n"
		"	addq  			$128, %%rbx 					\n"
		"   vfmadd231ps		%%zmm0, %%zmm7, %%zmm25 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm26 		\n"
		"	addq  			$16, %%rax 						\n"
		"   vfmadd231ps		%%zmm1, %%zmm7, %%zmm27 		\n"

		"   prefetcht0 		256(%%rax)                 		\n"

		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm28 		\n"
		"   vmovups 		(%%rbx), %%zmm4       			\n"
		"   vfmadd231ps		%%zmm2, %%zmm7, %%zmm29 		\n"

		"	vfmadd231ps		%%zmm3, %%zmm6, %%zmm30 		\n"
		"   vmovups 		64(%%rbx), %%zmm5       		\n"
		"	vfmadd231ps		%%zmm3, %%zmm7, %%zmm31 		\n"
		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"   prefetcht0 		64(%%rbx)                 		\n"

		".endm 												\n"



		".macro	KERNEL4x32_END_K							\n"

		"   vbroadcastss	8(%%rax), %%zmm2    			\n"
		"   vfmadd231ps		%%zmm0, %%zmm6, %%zmm24 		\n"
		"   vfmadd231ps		%%zmm0, %%zmm7, %%zmm25 		\n"

		"   vbroadcastss	12(%%rax), %%zmm3    			\n"
		"   vfmadd231ps		%%zmm1, %%zmm6, %%zmm26 		\n"
		"	addq  			$16, %%rax 						\n"
		"   vfmadd231ps		%%zmm1, %%zmm7, %%zmm27 		\n"

		"   vfmadd231ps		%%zmm2, %%zmm6, %%zmm28 		\n"
		"   vfmadd231ps		%%zmm2, %%zmm7, %%zmm29 		\n"

		"	vfmadd231ps		%%zmm3, %%zmm6, %%zmm30 		\n"
		"	vfmadd231ps		%%zmm3, %%zmm7, %%zmm31 		\n"

		".endm 												\n"


		".macro	ADD_C_4x32									\n"

		"   vmovups 		(%%r10), %%zmm0        			\n"
		"	vaddps 			%%zmm0, %%zmm24, %%zmm24		\n"
		"   vmovups 		64(%%r10), %%zmm1        		\n"
		"	vaddps 			%%zmm1, %%zmm25, %%zmm25		\n"
		"   vmovups 		(%%r11), %%zmm2        			\n"
		"	vaddps 			%%zmm2, %%zmm26, %%zmm26		\n"
		"   vmovups 		64(%%r11), %%zmm3        		\n"
		"	vaddps 			%%zmm3, %%zmm27, %%zmm27		\n"

		"   vmovups 		(%%r12), %%zmm4        			\n"
		"	vaddps 			%%zmm4, %%zmm28, %%zmm28		\n"
		"   vmovups 		64(%%r12), %%zmm5        		\n"
		"	vaddps 			%%zmm5, %%zmm29, %%zmm29		\n"
		"   vmovups 		(%%r13), %%zmm6        			\n"
		"	vaddps 			%%zmm6, %%zmm30, %%zmm30		\n"
		"   vmovups 		64(%%r13), %%zmm7        		\n"
		"	vaddps 			%%zmm7, %%zmm31, %%zmm31		\n"


		"	mov  	%%rcx, %%r10 							\n"  // C0
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3


		".endm 												\n"



		".macro	SAVE_4x32 									\n"

		"   vmovups 		%%zmm24, (%%r10)        		\n"
		"   vmovups 		%%zmm25, 64(%%r10)        		\n"
		"   vmovups 		%%zmm26, (%%r11)        		\n"
		"   vmovups 		%%zmm27, 64(%%r11)        		\n"
		"	subq 			$4, %%rdi 						\n"
		"   vmovups 		%%zmm28, (%%r12)        		\n"
		"   vmovups 		%%zmm29, 64(%%r12)        		\n"
		"   vmovups 		%%zmm30, (%%r13)        		\n"
		"   vmovups 		%%zmm31, 64(%%r13)        		\n"

		"	leaq  	(%%r13, %%r8, 4), %%rcx 				\n"  // C0


		".endm 												\n"


//-----------------------------------------------------------------
		"SMM_NN_KERNEL12x32:								\n"

		"   mov 	%[C], %%rcx   	 						\n"
		"   mov 	%[A], %%rax   	 						\n"
		"   mov 	%[B], %%rbx   	 						\n"

		"   prefetcht0 		(%%rax)                 		\n"

		"	mov 	%[K], %%rdx 							\n"  // K
		"	mov  	%[LN], %%r8 							\n" 
		"	mov  	%[Bc], %%r14 							\n"
		"	movq  	%[M], %%rdi 							\n"
		"	mov 	%[k_tag], %%r15 						\n"

		"   prefetcht0 		(%%rbx)                 		\n"
		"	mov 	%%rbx, %%r9 							\n"  // 
		"	mov 	%%rdx, %%rsi 							\n"  // K



		"BEGIN_PACK:										\n"

		"	mov 	%%r9, %%rbx 							\n"  // B
		"   prefetcht0 		(%%rbx)                 		\n" 

		"	mov  	%%rcx, %%r10 							\n"  // C0
		"   prefetcht2 		(%%r10)                 		\n"
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"   prefetcht2 		(%%r11)                 		\n"
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"   prefetcht2 		(%%r12)                 		\n"
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3
		"   prefetcht2 		(%%r13)                 		\n"

		"	mov 	%%rsi, %%rdx 							\n"  // K
		"	mov 	%%r14, %%rbp 							\n"  // Bc

		"   vmovups		(%%rbx), %%zmm4        				\n"
		"	vpxorq 		%%zmm8, %%zmm8, %%zmm8 				\n"
		"	vpxorq 		%%zmm9, %%zmm9, %%zmm9 				\n" 
		"	vpxorq 		%%zmm10, %%zmm10, %%zmm10 			\n" 
		"	vpxorq 		%%zmm11, %%zmm11, %%zmm11 			\n"  
		"   vmovups 	64(%%rbx), %%zmm5       			\n"

		"	vpxorq 		%%zmm12, %%zmm12, %%zmm12 			\n"
		"	vpxorq 		%%zmm13, %%zmm13, %%zmm13 			\n" 
		"	vpxorq 		%%zmm14, %%zmm14, %%zmm14 			\n" 
		"	vpxorq 		%%zmm15, %%zmm15, %%zmm15 			\n"
		"	vpxorq 		%%zmm16, %%zmm16, %%zmm16 			\n"
		"	vpxorq 		%%zmm17, %%zmm17, %%zmm17			\n" 
		"	vpxorq 		%%zmm18, %%zmm18, %%zmm18 			\n" 
		"	vpxorq 		%%zmm19, %%zmm19, %%zmm19 			\n"

		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vbroadcastss	4(%%rax), %%zmm1    			\n"

		"	vpxorq 		%%zmm20, %%zmm20, %%zmm20 			\n"
		"	vpxorq 		%%zmm21, %%zmm21, %%zmm21 			\n"
		"   prefetcht2 		64(%%r10)                 		\n"
		"	vpxorq 		%%zmm22, %%zmm22, %%zmm22 			\n" 
		"	vpxorq 		%%zmm23, %%zmm23, %%zmm23 			\n"
		"   prefetcht2 		64(%%r11)                 		\n"
		"	vpxorq 		%%zmm24, %%zmm24, %%zmm24 			\n"
		"	vpxorq 		%%zmm25, %%zmm25, %%zmm25			\n"
		"   prefetcht2 		64(%%r12)                 		\n"
		"	vpxorq 		%%zmm26, %%zmm26, %%zmm26 			\n" 
		"	vpxorq 		%%zmm27, %%zmm27, %%zmm27 			\n"
		"   prefetcht2 		64(%%r13)                 		\n"
		"	vpxorq 		%%zmm28, %%zmm28, %%zmm28 			\n"
		"	vpxorq 		%%zmm29, %%zmm29, %%zmm29			\n" 
		"	vpxorq 		%%zmm30, %%zmm30, %%zmm30 			\n" 
		"	vpxorq 		%%zmm31, %%zmm31, %%zmm31 			\n"   

		"	subq 	$8, %%rdx 								\n"

		"MAIN_PACK_K:										\n"


		"	KERNEL12x32_PACK_K1 							\n"
		"	KERNEL12x32_PACK_K2 							\n"
		"	KERNEL12x32_PACK_K1 							\n"
		"	KERNEL12x32_PACK_K2 							\n"
		"	KERNEL12x32_PACK_K1 							\n"
		"	KERNEL12x32_PACK_K2 							\n"
		"	KERNEL12x32_PACK_K1 							\n"
		"   cmp 	$0, %%rdx           					\n"
		"	je 		EDGE_PACK_K 							\n"
		"	KERNEL12x32_PACK_K2 							\n"

		"	subq 	$8, %%rdx 								\n"
		"   jmp     MAIN_PACK_K       						\n"
		

		"EDGE_PACK_K:										\n"

		"	KERNEL12x32_PACK_END_K 							\n"
		"	jmp  	BEGIN_SAVE 								\n"
		
//-----------------------------------------------------------------

		"BEGIN_M:											\n"

		"	mov 	%%r14, %%rbx 							\n"  // Bc
		"   prefetcht0 		(%%rbx)                 		\n" 

		"	mov  	%%rcx, %%r10 							\n"  // C0
		"   prefetcht1 		(%%r10)                 		\n"
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"   prefetcht1 		(%%r11)                 		\n"
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"   prefetcht1 		(%%r12)                 		\n"
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3
		"   prefetcht1 		(%%r13)                 		\n"

		"	mov 	%%rsi, %%rdx 							\n"  // K

		"BEGIN_K:											\n"

		"   vmovups		(%%rbx), %%zmm4        				\n"
		"	vpxorq 		%%zmm8, %%zmm8, %%zmm8 				\n"
		"	vpxorq 		%%zmm9, %%zmm9, %%zmm9 				\n" 
		"	vpxorq 		%%zmm10, %%zmm10, %%zmm10 			\n" 
		"	vpxorq 		%%zmm11, %%zmm11, %%zmm11 			\n"  
		"   vmovups 	64(%%rbx), %%zmm5       			\n"

		"	vpxorq 		%%zmm12, %%zmm12, %%zmm12 			\n"
		"	vpxorq 		%%zmm13, %%zmm13, %%zmm13 			\n" 
		"	vpxorq 		%%zmm14, %%zmm14, %%zmm14 			\n" 
		"	vpxorq 		%%zmm15, %%zmm15, %%zmm15 			\n"
		"	vpxorq 		%%zmm16, %%zmm16, %%zmm16 			\n"
		"	vpxorq 		%%zmm17, %%zmm17, %%zmm17			\n" 
		"	vpxorq 		%%zmm18, %%zmm18, %%zmm18 			\n" 
		"	vpxorq 		%%zmm19, %%zmm19, %%zmm19 			\n"

		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vbroadcastss	4(%%rax), %%zmm1    			\n"

		"	vpxorq 		%%zmm20, %%zmm20, %%zmm20 			\n"
		"	vpxorq 		%%zmm21, %%zmm21, %%zmm21 			\n" 
		"	vpxorq 		%%zmm22, %%zmm22, %%zmm22 			\n" 
		"	vpxorq 		%%zmm23, %%zmm23, %%zmm23 			\n"
		"	vpxorq 		%%zmm24, %%zmm24, %%zmm24 			\n"
		"	vpxorq 		%%zmm25, %%zmm25, %%zmm25			\n" 
		"	vpxorq 		%%zmm26, %%zmm26, %%zmm26 			\n" 
		"	vpxorq 		%%zmm27, %%zmm27, %%zmm27 			\n"
		"	vpxorq 		%%zmm28, %%zmm28, %%zmm28 			\n"
		"	vpxorq 		%%zmm29, %%zmm29, %%zmm29			\n" 
		"	vpxorq 		%%zmm30, %%zmm30, %%zmm30 			\n" 
		"	vpxorq 		%%zmm31, %%zmm31, %%zmm31 			\n"   

		"	subq 	$8, %%rdx 								\n"

		"MAIN_K:											\n"


		"	KERNEL12x32_K1 									\n"
		"	KERNEL12x32_K2 									\n"
		"	KERNEL12x32_K1 									\n"
		"	KERNEL12x32_K2 									\n"
		"	KERNEL12x32_K1 									\n"
		"	KERNEL12x32_K2 									\n"
		"	KERNEL12x32_K1 									\n"
		"   cmp 	$0, %%rdx           					\n"
		"	je 		EDGE_K 									\n"
		"	KERNEL12x32_K2 									\n"

		"	subq 	$8, %%rdx 								\n"
		"   jmp     MAIN_K       							\n"
		
		"EDGE_K:											\n"

		"	KERNEL12x32_END_K 								\n"


		"BEGIN_SAVE:										\n"
		"	cmp 	$0, %%r15								\n"
		"	je  	SAVE_C 									\n"
		"	ADD_C_12x32 									\n"
		"SAVE_C: 											\n"
		"	SAVE_12x32 										\n"

		"	cmpq  	$12, %%rdi 								\n"
		"	jnb 	BEGIN_M 								\n"


//----------------------------------------------------------------
		"EDGE_M:											\n"
		"	cmpq  	$8, %%rdi  								\n"   //M % 12
		"	jb   	BEGIN_M4 								\n"

		"BEGIN_M8:											\n"

		"	mov 	%%r14, %%rbx 							\n"  // Bc
		"   prefetcht0 		(%%rbx)                 		\n" 

		"	mov  	%%rcx, %%r10 							\n"  // C0
		"   prefetcht2 		(%%r10)                 		\n"
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"   prefetcht2 		(%%r11)                 		\n"
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"   prefetcht2 		(%%r12)                 		\n"
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3
		"   prefetcht2 		(%%r13)                 		\n"

		"	mov 	%%rsi, %%rdx 							\n"  // K

		"   vmovups		(%%rbx), %%zmm4        				\n"
		"	vpxorq 		%%zmm16, %%zmm16, %%zmm16 			\n"
		"	vpxorq 		%%zmm17, %%zmm17, %%zmm17			\n"
		"   vmovups 	64(%%rbx), %%zmm5       			\n"
		"	vpxorq 		%%zmm18, %%zmm18, %%zmm18 			\n" 
		"	vpxorq 		%%zmm19, %%zmm19, %%zmm19 			\n"

		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   vbroadcastss	4(%%rax), %%zmm1    			\n"

		"	vpxorq 		%%zmm20, %%zmm20, %%zmm20 			\n"
		"	vpxorq 		%%zmm21, %%zmm21, %%zmm21 			\n"
		"   prefetcht2 		64(%%r10)                 		\n"
		"	vpxorq 		%%zmm22, %%zmm22, %%zmm22 			\n" 
		"	vpxorq 		%%zmm23, %%zmm23, %%zmm23 			\n"
		"   prefetcht2 		64(%%r11)                 		\n"
		"	vpxorq 		%%zmm24, %%zmm24, %%zmm24 			\n"
		"	vpxorq 		%%zmm25, %%zmm25, %%zmm25			\n"
		"   prefetcht2 		64(%%r12)                 		\n"
		"	vpxorq 		%%zmm26, %%zmm26, %%zmm26 			\n" 
		"	vpxorq 		%%zmm27, %%zmm27, %%zmm27 			\n"
		"   prefetcht2 		64(%%r13)                 		\n"
		"	vpxorq 		%%zmm28, %%zmm28, %%zmm28 			\n"
		"	vpxorq 		%%zmm29, %%zmm29, %%zmm29			\n" 
		"	vpxorq 		%%zmm30, %%zmm30, %%zmm30 			\n" 
		"	vpxorq 		%%zmm31, %%zmm31, %%zmm31 			\n"   

		"	subq 	$8, %%rdx 								\n"

		"MAIN_K_M8:											\n"


		"	KERNEL8x32_K1 									\n"
		"	KERNEL8x32_K2 									\n"
		"	KERNEL8x32_K1 									\n"
		"	KERNEL8x32_K2 									\n"
		"	KERNEL8x32_K1 									\n"
		"	KERNEL8x32_K2 									\n"
		"	KERNEL8x32_K1 									\n"
		"   cmp 	$0, %%rdx           					\n"
		"	je 		EDGE_K_M8 								\n"
		"	KERNEL8x32_K2 									\n"

		"	subq 	$8, %%rdx 								\n"
		"   jmp     MAIN_K_M8       						\n"
		

		"EDGE_K_M8:											\n"

		"	KERNEL8x32_END_K 								\n"

		"	cmp 	$0, %%r15								\n"
		"	je  	SAVE_C_8x32 							\n"
		"	ADD_C_8x32 										\n"
		"SAVE_C_8x32: 										\n"
		"	SAVE_8x32 										\n"



//----------------------------------------------------------------
		"BEGIN_M4:											\n"

		"	cmpq  	$4, %%rdi  								\n"   //M % 12
		"	jb   	END_M 									\n"


		"	mov 	%%r14, %%rbx 							\n"  // Bc
		"   prefetcht0 		(%%rbx)                 		\n" 

		"	mov  	%%rcx, %%r10 							\n"  // C0
		"   prefetcht2 		(%%r10)                 		\n"
		"	leaq 	(%%r10, %%r8, 4), %%r11 				\n"	 // C1
		"   prefetcht2 		(%%r11)                 		\n"
		"	leaq 	(%%r11, %%r8, 4), %%r12 				\n"  // C2
		"   prefetcht2 		(%%r12)                 		\n"
		"	leaq 	(%%r12, %%r8, 4), %%r13 				\n"  // C3
		"   prefetcht2 		(%%r13)                 		\n"

		"	mov 	%%rsi, %%rdx 							\n"  // K

		"   vmovups		(%%rbx), %%zmm4        				\n"
		"   vmovups 	64(%%rbx), %%zmm5       			\n"

		"   prefetcht2 		64(%%r10)                 		\n"
		"	vpxorq 		%%zmm24, %%zmm24, %%zmm24 			\n"
		"	vpxorq 		%%zmm25, %%zmm25, %%zmm25			\n"
		"   vbroadcastss	(%%rax), %%zmm0    				\n"
		"   prefetcht2 		64(%%r11)                 		\n"
		"	vpxorq 		%%zmm26, %%zmm26, %%zmm26 			\n" 
		"	vpxorq 		%%zmm27, %%zmm27, %%zmm27 			\n"
		"   vbroadcastss	4(%%rax), %%zmm1    			\n"
		"   prefetcht2 		64(%%r12)                 		\n"
		"	vpxorq 		%%zmm28, %%zmm28, %%zmm28 			\n"
		"	vpxorq 		%%zmm29, %%zmm29, %%zmm29			\n"
		"   prefetcht2 		64(%%r13)                 		\n" 
		"	vpxorq 		%%zmm30, %%zmm30, %%zmm30 			\n" 
		"	vpxorq 		%%zmm31, %%zmm31, %%zmm31 			\n"   

		"	subq 	$8, %%rdx 								\n"

		"MAIN_K_M4:											\n"


		"	KERNEL4x32_K1 									\n"
		"	KERNEL4x32_K2 									\n"
		"	KERNEL4x32_K1 									\n"
		"	KERNEL4x32_K2 									\n"
		"	KERNEL4x32_K1 									\n"
		"	KERNEL4x32_K2 									\n"
		"	KERNEL4x32_K1 									\n"
		"   cmp 	$0, %%rdx           					\n"
		"	je 		EDGE_K_M4 								\n"
		"	KERNEL4x32_K2 									\n"

		"	subq 	$8, %%rdx 								\n"
		"   jmp     MAIN_K_M4       						\n"
		

		"EDGE_K_M4:											\n"

		"	KERNEL4x32_END_K 								\n"

		"	cmp 	$0, %%r15								\n"
		"	je  	SAVE_C_4x32 							\n"
		"	ADD_C_4x32 										\n"
		"SAVE_C_4x32: 										\n"
		"	SAVE_4x32 										\n"

		"END_M:												\n"


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
		 [Bc] "m" (Bc),
		 [k_tag] "m" (k_tag)   
		:
		 "rax", "rbx", "rcx", "rdx", "rdi", "rsi","rbp","r8", "r9", "r10", "r11", "r12",
		 "r13", "r14", "r15", "zmm0", "zmm1", "zmm2", "zmm3", "zmm4", "zmm5",
		 "zmm6", "zmm7", "zmm8", "zmm9", "zmm10", "zmm11", "zmm12", "zmm13",
		 "zmm14", "zmm15", "zmm16", "zmm17", "zmm18", "zmm19", "zmm20", "zmm21",
		 "zmm22", "zmm23", "zmm24", "zmm25", "zmm26", "zmm27", "zmm28", "zmm29",
		 "zmm30", "zmm31", "memory"
    
    );

}