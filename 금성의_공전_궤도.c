#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double fx(double x, double y)
{
	double Gm1 = 2.168*1e14, Gm2 = 1.327*1e20;
	double result;
	result = x*(-Gm1-Gm2)/pow(x*x+y*y, 1.5);
	return result;
}

double fy(double x, double y)
{
	double Gm1 = 2.168*1e14, Gm2 = 1.327*1e20;
	double result;
	result = y*(-Gm1-Gm2)/pow(x*x+y*y, 1.5);
	return result;
}

int main()
{
	double t, x, y, vx, vy, h;
	double k1, k2, k3, k4, l1, l2, l3, l4, q1, q2, q3, q4, s1, s2, s3, s4;	
	double L, E, G, m1, m2, mu, k, rdot, r;
	int day, prev_day = -1;

	FILE* fp;

	fp = fopen("Venus_orbit_E_L", "w");

	G = 6.674*1e-11;
	m1 = 2.168*1e14/G, m2 = 1.327*1e20/G;
	mu = m1*m2/(m1+m2), k = G*m1*m2;

	t = 0, x = 1.075*1e11, y = 0, vx = 0, vy = 3.525*1e4, h = 1e-1;
	while(1)
	{
		day = t/(3600*24);
		if(day > prev_day)
		{
			L = mu*(vy*x-vx*y);
			r = pow(x*x+y*y, 0.5);
			rdot = vx*x/r + vy*y/r;
			E = mu*rdot*rdot/2.0 + L*L/(2.0*mu*r*r) - k/r;
			fprintf(fp, "%d %f %f %g %g\n", day, x, y, L, E);
			//printf("%d %f %f %g %g\n", day, x, y, L, E);
		}

		prev_day = t/(3600*24);

		k1 = h*vx, l1 = h*vy, q1 = h*fx(x, y), s1 = h*fy(x, y);
		k2 = h*(vx+q1/2.0), l2 = h*(vy+s1/2.0), q2 = h*fx(x+k1/2.0, y+l1/2.0), s2 = h*fy(x+k1/2.0, y+l1/2.0);
		k3 = h*(vx+q2/2.0), l3 = h*(vy+s2/2.0), q3 = h*fx(x+k2/2.0, y+l2/2.0), s3 = h*fy(x+k2/2.0, y+l2/2.0);
		k4 = h*(vx+q3), l4 = h*(vy+s3), q4 = h*fx(x+k3, y+l3), s4 = h*fy(x+k3, y+l3);

		x = x + (k1 + 2.0*k2 + 2.0*k3 + k4)/6.0;	
		y = y + (l1 + 2.0*l2 + 2.0*l3 + l4)/6.0;
		vx = vx + (q1 + 2.0*q2 + 2.0*q3 + q4)/6.0;
		vy = vy + (s1 + 2.0*s2 + 2.0*s3 + s4)/6.0;

		if(day > 225)
			break;

		t = t+h;
	}

	return 0;
}
