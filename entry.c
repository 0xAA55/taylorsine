#include<stdio.h>
#include<math.h>
#include<inttypes.h>

typedef long double real_t, *real_p;

#ifndef X_REPEAT
#define X_REPEAT 1
#endif

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348
#define PI_Half (PI * 0.5)
#define PI_2 6.2831853071795864769252867665590057683943387987502116419498891846156328125724179972560696

real_t sgn(real_t x)
{
	if(x > 0) return 1;
	if(x < 0) return -1;
	return 0;
}

real_t sine_tyler(real_t x)
{
	real_t result;
	real_t cur_pow = 3;
	real_t cur_div = 6;
	real_t cur_sgn = -1;
	
#if X_REPEAT
	x = fmod(x + PI, PI_2) - PI;
	if(fabs(x) > PI_Half) x = PI - x;
#endif

	result = x;
	for(;;)
	{
		real_t last_result = result;
		result += cur_sgn * pow(x, cur_pow) / cur_div;
		if(result == last_result) break;
		cur_div *= (cur_pow + 1) * (cur_pow + 2);
		cur_pow += 2;
		cur_sgn *= -1;
	}
	
	return result;
}

int main(int argc, char **argv)
{
	int i, slices = 256, periods = 4;
	
	for( i = 0; i < slices; i++)
	{
		double sinx = PI_2 * i * periods / slices;
		double s = (double)sine_tyler(sinx);
		printf("%.20lf, %.20lf\n", s, sinf(sinx));
	}
	return 0;
}
