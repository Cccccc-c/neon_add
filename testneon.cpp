#include <arm_neon.h>
#include <stdio.h>
#include <time.h>

void test1(int nn ,float *ptr,float *ptr1, float *outptr)
{
        float *a = ptr;
	float *b = ptr1;
	float *c = outptr;

        clock_t start, end;
        double cpu_time_used;

        start = clock();

        // int nn = num / 4;
	asm volatile(
                "0:                               \n"
                "ld1        {v0.4s}, [%1], #16    \n"
                "ld1        {v1.4s}, [%2], #16    \n"
                "fadd       v0.4s, v0.4s, v1.4s   \n"
                "subs       %w0, %w0, #1          \n"
                "st1        {v0.4s}, [%3], #16    \n"
                "bne        0b                  \n"
                : "=r"(nn),    // %0
                "=r"(ptr),   // %1
                "=r"(ptr1),  // %2
                "=r"(outptr) // %3
                : "0"(nn),
                "1"(ptr),
                "2"(ptr1),
                "3"(outptr)
                : "cc", "memory", "v0", "v1");

        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("CPU 时间已用： %f ms\n", cpu_time_used*1000);

	for(int i=0;i<4;i++)
        {
                printf("%f %f %f\n",a[i],b[i],c[i]);
        }
}

void test2(int nn ,float *ptr,float *ptr1, float *outptr)
{
        float *a = ptr;
	float *b = ptr1;
	float *c = outptr;

        clock_t start, end;
        double cpu_time_used;

        start = clock();

	asm volatile(
                 "0:                               \n"
                 "ld1        {v0.4s,v1.4s,v2.4s,v3.4s}, [%1], #64    \n"
                 "ld1        {v4.4s,v5.4s,v6.4s,v7.4s}, [%2], #64    \n"
                 "fadd       v0.4s, v0.4s, v4.4s   \n"
                 "fadd       v1.4s, v1.4s, v5.4s   \n"
                 "fadd       v2.4s, v2.4s, v6.4s   \n"
                 "fadd       v3.4s, v3.4s, v7.4s   \n"
                 "subs       %w0, %w0, #1          \n"
                 "st1        {v0.4s,v1.4s,v2.4s,v3.4s}, [%3], #64    \n"
                 "bne        0b                  \n"
                 : "=r"(nn),    // %0
                 "=r"(ptr),   // %1
                 "=r"(ptr1),  // %2
                 "=r"(outptr) // %3
                 : "0"(nn),
                 "1"(ptr),
                 "2"(ptr1),
                 "3"(outptr)
                 : "cc", "memory", "v0", "v1", "v2", "v3","v4", "v5", "v6", "v7");

        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("CPU 时间已用： %f ms\n", cpu_time_used*1000);

	for(int i=0;i<4;i++)
        {
                printf("%f %f %f\n",a[i],b[i],c[i]);
        }
}

void test3(int nn ,float *ptr,float *ptr1, float *outptr)
{
        float *a = ptr;
	float *b = ptr1;
	float *c = outptr;

        clock_t start, end;
        double cpu_time_used;

        start = clock();

       for(int i=0;i<nn;i++){
                float32x4_t _f32_1_ = vld1q_f32(ptr + i * 16 + 0);
                float32x4_t _f32_2_ = vld1q_f32(ptr + i * 16 + 4);
                float32x4_t _f32_3_ = vld1q_f32(ptr + i * 16 + 8);
                float32x4_t _f32_4_ = vld1q_f32(ptr + i * 16 + 12);
                float32x4_t _f32_2_1 = vld1q_f32(ptr1 + i * 16 + 0);
                float32x4_t _f32_2_2 = vld1q_f32(ptr1 + i * 16 + 4);
                float32x4_t _f32_2_3 = vld1q_f32(ptr1 + i * 16 + 8);
                float32x4_t _f32_2_4 = vld1q_f32(ptr1 + i * 16 + 12);
                _f32_1_ = vaddq_f32(_f32_1_,_f32_2_1);
                _f32_2_ = vaddq_f32(_f32_2_,_f32_2_2);
                _f32_3_ = vaddq_f32(_f32_3_,_f32_2_3);
                _f32_4_ = vaddq_f32(_f32_4_,_f32_2_4);
                vst1q_f32(outptr + i * 16 + 0, _f32_1_);
                vst1q_f32(outptr + i * 16 + 4, _f32_2_);
                vst1q_f32(outptr + i * 16 + 8, _f32_3_);
                vst1q_f32(outptr + i * 16 + 12, _f32_4_);
        }

        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("CPU 时间已用： %f ms\n", cpu_time_used*1000);

	for(int i=0;i<4;i++)
        {
                printf("%f %f %f\n",a[i],b[i],c[i]);
        }
}

void test4(int nn ,float *ptr,float *ptr1, float *outptr)
{
        float *a = ptr;
	float *b = ptr1;
	float *c = outptr;

        clock_t start, end;
        double cpu_time_used;

        start = clock();

        for(int i=0;i<nn;i++)
        {
                outptr[i] = ptr[i] + ptr1[i];
        }

        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("CPU 时间已用： %f ms\n", cpu_time_used*1000);

	for(int i=0;i<4;i++)
        {
                printf("%f %f %f\n",a[i],b[i],c[i]);
        }
}

void test5(int nn ,float *ptr,float *ptr1, float *outptr)
{
        float *a = ptr;
	float *b = ptr1;
	float *c = outptr;

        clock_t start, end;
        double cpu_time_used;

        start = clock();

        for(int i=0;i<nn;i++)
        {
                asm volatile(
                "ld1        {v0.4s}, [%0], #16    \n"
		"ld1        {v1.4s}, [%0], #16    \n"
		"ld1        {v2.4s}, [%0], #16    \n"
		"ld1        {v3.4s}, [%0], #16    \n"
		"ld1        {v4.4s}, [%1], #16    \n"
                "ld1        {v5.4s}, [%1], #16    \n"
                "ld1        {v6.4s}, [%1], #16    \n"
                "ld1        {v7.4s}, [%1], #16    \n"
                "fadd       v0.4s, v0.4s, v4.4s   \n"
                "fadd       v1.4s, v1.4s, v5.4s   \n"
                "fadd       v2.4s, v2.4s, v6.4s   \n"
                "fadd       v3.4s, v3.4s, v7.4s   \n"
                "st1        {v0.4s}, [%2], #16    \n"
                "st1        {v1.4s}, [%2], #16    \n"
		"st1        {v2.4s}, [%2], #16    \n"
		"st1        {v3.4s}, [%2], #16    \n"
		:"=r"(ptr),   // %0
                "=r"(ptr1),  // %1
                "=r"(outptr) // %2
                :"0"(ptr),
                "1"(ptr1),
                "2"(outptr)
                : "cc", "memory", "v0", "v1", "v2", "v3","v4", "v5", "v6", "v7");
        }

        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("CPU 时间已用： %f ms\n", cpu_time_used*1000);

	for(int i=0;i<4;i++)
        {
                printf("%f %f %f\n",a[i],b[i],c[i]);
        }
}

int main()
{
        int num = 4*1000000;
        float *ptr = new float[num];
        float *ptr1 = new float[num];
	float *outptr = new float[num];
	
	for(int i=0;i<num;i++)
	{
                ptr[i] = 1;
                ptr1[i] = 1;
                outptr[i] = 0;
	}
	
	int nn = num / 4 / 4;
        test1(num/4 ,ptr,ptr1, outptr);

        test2(num/4/4 ,ptr,ptr1, outptr);

        test3(num/4/4 ,ptr,ptr1, outptr);

        test4(num ,ptr,ptr1, outptr);

        test5(num/4/4 ,ptr,ptr1, outptr);
       
        return 0;
}
