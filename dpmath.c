#include <math.h>

long double AspectRatio (h, v)
	long double h, v;
{
	return h / v;
}

long double OneInchDistance (acuity)
	long double acuity;
{
   	return 1 / ((acuity / 20) / 3438);
}

long double PPI (h, v, size)
	long double h, v, size; /* h/v in pixels, size in inches */
{
	return sqrtl (powl (h, 2) + powl (v, 2)) / size;
}

long double DiagResolution (size, ppi)
	long double size, ppi;
{
	return powl (size * ppi, 2);
}

long double VResFromDiag (d, r)
	long double d, r;
{
	return sqrtl (d / (powl (r, 2) + 1));
}

long double PhysVRes (s, r)
	long double s, r;
{
	return sqrtl (powl (s, 2) / ((powl (r, 2)) + 1));
}

long double DisplaySize (h, v, ppi)
	long double h, v, ppi;
{
	return sqrtl (powl (h, 2) + powl (v, 2)) / ppi;
}

long double OptimalPPI (distance, acuity)
	long double distance, acuity;
{
 	return (1 / distance) * OneInchDistance (acuity);
}

long double AdjustedAcuity (acuity, cycles)
	long double acuity, cycles;
{
 	return acuity / (cycles / 30);
}