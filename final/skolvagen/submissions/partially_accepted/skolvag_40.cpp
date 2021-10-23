#include <stdio.h>
#include <string.h>
#include <assert.h>

int MIN(int p,int q) {return p<q?p:q;}

int main() {
  char kors[1001];
  int N,n,s,ss,i;
  scanf("%s", kors);
  N=strlen(kors);
  assert(N <= 20);
  n=0;
  s=1000000;
  for(i=0;i<=2*N;i++) {
    if(i%2==0) {
      ss=MIN(s,n+1);
      n=MIN(n,s+1);
      s=ss;
    }
    else switch(kors[i/2]) {
      case 'N': n++; break;
      case 'S': s++; break;
      case 'B': n++; s++; break;
      }
  }
  printf("%d\n",n);
  return 0;
}
