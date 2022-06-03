#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double fx(double x, double y)
{
	double Gm1 = 1.0*1e-5, Gm2 = 4.0*1e14;
	double result;
	result = x*(-Gm1-Gm2)/pow(x*x+y*y, 1.5);
	return result;
}

double fy(double x, double y)
{
	double Gm1 = 1.0*1e-5, Gm2 = 4.0*1e14;
	double result;
	result = y*(-Gm1-Gm2)/pow(x*x+y*y, 1.5);
	return result;
}

	
int main()
{	
	double t, r0, x, y, vx, vy, h;
	double k1, k2, k3, k4, l1, l2, l3, l4, q1, q2, q3, q4, s1, s2, s3, s4;	
	int hour, prev_hour = -1;
	double Gm1 = 1.0*1e-5, Gm2 = 4.0*1e14;
	r0 = pow(86400/(2*M_PI),0.6)*pow(Gm1+Gm2,0.3);

//	printf("%f\n",r0);
	FILE* fp;
	fp = fopen("Geostationary_orbit", "w");

	t = 0, x = r0, y = 0, vx = 0, vy = pow((1.0*1e-5 + 4.0*1e14)/r0, 0.5), h = 1e-1;
	while(1)
	{
		hour = t/(3600);
		
		if(hour > prev_hour)
		{	
			fprintf(fp, "%d %f %f\n", hour, x, y);
			
		}

		prev_hour = t/3600;	

		k1 = h*vx, l1 = h*vy, q1 = h*fx(x, y), s1 = h*fy(x, y);
		k2 = h*(vx+q1/2.0), l2 = h*(vy+s1/2.0), q2 = h*fx(x+k1/2.0, y+l1/2.0), s2 = h*fy(x+k1/2.0, y+l1/2.0);
		k3 = h*(vx+q2/2.0), l3 = h*(vy+s2/2.0), q3 = h*fx(x+k2/2.0, y+l2/2.0), s3 = h*fy(x+k2/2.0, y+l2/2.0);
		k4 = h*(vx+q3), l4 = h*(vy+s3), q4 = h*fx(x+k3, y+l3), s4 = h*fy(x+k3, y+l3);

		x = x + (k1 + 2.0*k2 + 2.0*k3 + k4)/6.0;	
		y = y + (l1 + 2.0*l2 + 2.0*l3 + l4)/6.0;
		vx = vx + (q1 + 2.0*q2 + 2.0*q3 + q4)/6.0;
		vy = vy + (s1 + 2.0*s2 + 2.0*s3 + s4)/6.0;

		if(hour > 23)
			break;

		t = t+h;
	}

	return 0;
}
