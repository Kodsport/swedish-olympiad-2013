#include <stdio.h>
#include <stdlib.h>

void scan(int n, int np, int x[],int ord[], int d[], int rev) {
  int i,j;
  int nact=0,last=0,sum=0;
  for(i=0;i<n;i++) {
    j=(rev==-1)?ord[n-1-i]:ord[i];
    sum+=nact*(x[j]-last)*rev;
    if(j>=np) d[j]+=sum;
    else nact++;
    last=x[j];
  }
}

int x[200000],y[200000];

int fcmpx(const void *v1, const void *v2) {
  return x[*(int*)v1]-x[*(int*)v2];
}
int fcmpy(const void *v1, const void *v2) {
  return y[*(int*)v1]-y[*(int*)v2];
}

int main() {
  int d[100000],ordx[200000], ordy[200000],i,n,np,min;
  scanf("%d %d", &np, &i);
  n=np+i;
  for(i=0;i<n;i++) {
    scanf("%d %d", &x[i],&y[i]);
    ordx[i]=ordy[i]=i;
    if(i>=np) d[i]=0;
  }
  qsort(ordx,n,sizeof(int),fcmpx);
  qsort(ordy,n,sizeof(int),fcmpy);
  scan(n,np,x,ordx,d,1);
  scan(n,np,x,ordx,d,-1);
  scan(n,np,y,ordy,d,1);
  scan(n,np,y,ordy,d,-1);
  min=1000000000;
  for(i=np;i<n;i++) if(d[i]<min) min=d[i];
  printf("%d\n", min);
  return 0;
}
