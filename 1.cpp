//27.	F(x) = (cos(x) + 1) / (sin(x) + 4)

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
//#include <ctime>
//#include <Windows.h>

void main()
{
	double a = -1000, b = 1000, step = 0.00001, x, f;
	int four = 4;
	int one = 1;
	clock_t start, end;
	//LARGE_INTEGER freq, t1, t2;
	//QueryPerformanceFrequency(&freq);

	x = a;
	f = 0;
	start = clock();
	//QueryPerformanceCounter(&t1);

	_asm
	{
		finit				// инициализировать FPU
		fld b				// пихаем b в стек

		fld x				// пихаем х в стек

loop_start:
		fcom				// сравнивает st0 и st1 (тек позицию и MAX)
		fstsw ax			// в ax пихаем значение регистра состояния? 
		and ah, 01000101b	//сохраняем значения только C0 C2 C3
		jz loop_end			//Если С3 = 1 (st0 == st1), то выход

		fld x				// пихаем х в стек
		fcos				// cos (st0)
		fiadd one			// st0 + целое число 1

		fld x				// пихаем х в стек
		fsin				// sin (st0)
		fiadd four			// st0 + целое число 4

		fdiv				// st0/st1
		fadd f				// результат деления + f
		fstp f				// пихаем в F значение из st0 и удаляем st0

		fadd step			//добавили шаг в st0
		fst x				// в х пихнули st0

		jmp loop_start
loop_end:
		fwait				// если проц накосячил, то подаждём его
	}

	end = clock();
	//QueryPerformanceCounter(&t2);
	//cout << "C: t = " << (t2.QuadPart - t1.QuadPart) << "\tF = " << f << endl;
	printf("\ntime asm = %f", (double)(end-start)/ CLK_TCK);
	printf("\nf = %f", f);
	system("pause");

	x = a;
	f = 0;
	start = clock();
	//QueryPerformanceCounter(&t1);

	while(x <= b)
	{
		f += (cos(x) + 1) / (sin(x) + 4);
		x += step;
	}

	end = clock();
	//QueryPerformanceCounter(&t2);
	//cout << "C: t = " << (t2.QuadPart - t1.QuadPart) << "\tF = " << f << endl;
	printf("\ntime cpp = %f", (double)(end-start)/ CLK_TCK);
	printf("\nf = %f", f);
	system("pause");

}