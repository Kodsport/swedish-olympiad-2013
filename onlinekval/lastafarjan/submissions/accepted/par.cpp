#include <stdio.h>

int T[101][101][101], U[101][101][101];

int main() {
  int N,L,i,j,k,n,q[4],h,heff,ok;
  scanf("%d %d\n", &N, &L);
  for(i=0;i<=L;i++) for(j=0;j<=L;j++) for(k=0;k<=L;k++) T[i][j][k]=-1;  
  T[0][0][0]=0;
  for(n=0;n<N;n++) {
    scanf("%d", &h);
    for(i=0;i<=L;i++) for(j=0;j<=L;j++) for(k=0;k<=L;k++) U[i][j][k]=-1;
    ok=0;
    for(q[0]=0;q[0]<=L;q[0]++) for(q[1]=0;q[1]<=L;q[1]++) for(q[2]=0;q[2]<=L;q[2]++) {
      q[3]=T[q[0]][q[1]][q[2]];
      if(q[3]>=0) {
        for(i=0;i<4;i++) {
              heff=q[i]==0?h:h+1;
              if(q[i]+heff<=L) {
        ok=1;
        q[i]+=heff;
        if(U[q[0]][q[1]][q[2]]<0 || q[3]<U[q[0]][q[1]][q[2]]) U[q[0]][q[1]][q[2]]=q[3];
        q[i]-=heff;
              }
        }
      }
    }    
    if(!ok) break;
    for(i=0;i<=L;i++) for(j=0;j<=L;j++) for(k=0;k<=L;k++) T[i][j][k]=U[i][j][k];
  }
  printf("%d\n", n);
  return 0;
}

