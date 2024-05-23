#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

void scan(ll n, ll np, ll x[],ll ord[], ll d[], ll rev) {
  ll i,j;
  ll nact=0,last=0,sum=0;
  for(i=0;i<n;i++) {
    j=(rev==-1)?ord[n-1-i]:ord[i];
    sum+=nact*(x[j]-last)*rev;
    if(j>=np) d[j]+=sum;
    else nact++;
    last=x[j];
  }
}

ll x[200000],y[200000];

int fcmpx(const void *v1, const void *v2) {
  return x[*(ll*)v1]-x[*(ll*)v2];
}
int fcmpy(const void *v1, const void *v2) {
  return y[*(ll*)v1]-y[*(ll*)v2];
}

int main() {
  ll d[200000],ordx[200000], ordy[200000],i,n,np,min;
  scanf("%lld %lld", &np, &i);
  n=np+i;
  for(i=0;i<n;i++) {
    scanf("%lld %lld", &x[i],&y[i]);
    ordx[i]=ordy[i]=i;
    if(i>=np) d[i]=0;
  }
  qsort(ordx,n,sizeof(ll),fcmpx);
  qsort(ordy,n,sizeof(ll),fcmpy);
  scan(n,np,x,ordx,d,1);
  scan(n,np,x,ordx,d,-1);
  scan(n,np,y,ordy,d,1);
  scan(n,np,y,ordy,d,-1);
  min=1LL<<62;
  for(i=np;i<n;i++)  {
    if(d[i]<min)  { 
  //      printf("ans is now %lld\n",min);
        min=d[i];
    }
  }
  printf("%lld\n", min);
  return 0;
}
