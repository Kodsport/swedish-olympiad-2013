#include <stdio.h>
#include <math.h>

double x[100000], y[100000];
double thre=1.0e-9;
int N;

double f(double xx) {
  double sum=0;
  int i;
  for(i=0;i<N;i++) sum+=sqrt((x[i]-xx)*(x[i]-xx)+y[i]*y[i]);
  return sum;
}

double tersearch(double x0, double x3) {
  double x1,x2,z1,z2;
  if(x3-x0<thre) return 0.5*(x0+x3);
  x1=x0+0.33333*(x3-x0);
  x2=x0+0.66667*(x3-x0);
  z1=f(x1);
  z2=f(x2);
  if(z1>z2) return tersearch(x1,x3);
  else return  tersearch(x0,x2);
}

int main() {
  double xmax,xmin;
  int i;
  scanf("%d", &N);
  
  for(i=0;i<N;i++) {
    scanf("%lf %lf", &x[i], &y[i]);
    if(i==0 || x[i]>xmax) xmax=x[i];
    if(i==0 || x[i]<xmin) xmin=x[i];
  }
  printf("%lf\n",2.0*f(tersearch(xmin,xmax)));
  return 0;
}
