#include <stdio.h>

int main() {
  int N,K,i,j,k,b[100][100],c[202][1001],left[202],nr,t,bingo;
  scanf("%d %d",&N,&K);
  for(i=0;i<N;i++) for(j=0;j<N;j++) scanf("%d", &b[i][j]);
  
  nr=2*N+2;
  for(i=0;i<nr;i++) {
    for(j=0;j<=1000;j++) c[i][j]=0;
    left[i]=N;
  }
  for(i=0;i<N;i++) for(j=0;j<N;j++) {
      c[i][b[i][j]]++;
      c[i+N][b[j][i]]++;
      if(i==j) c[2*N][b[i][j]]++;
      if(i+j==N-1) c[2*N+1][b[i][j]]++;
    }
  bingo=0;
  for(k=0;k<K && !bingo;k++) {
    scanf("%d", &t);
    for(i=0;i<nr;i++) if(c[i][t]>0) {
	c[i][t]--;
	left[i]--;
	if(left[i]==0) bingo=1;
    }
  }
  if(bingo) printf("%d\n",k);
  else printf("-1\n");
  return 0;
}
