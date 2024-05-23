#include <stdio.h>

int main() {
  int N,P,s[30],st[30],t[30],cs[30],bra[30],a[100],b[100],mx[100],max,tot,i,j;
  scanf("%d %d",&N,&P);
  for(i=0;i<N-1;i++) scanf("%d", &s[i]);
  cs[0]=0;
  for(j=1;j<N;j++) cs[j]=cs[j-1]+s[j-1];
  for(i=0;i<P;i++) {scanf("%d %d %d", &a[i],&b[i],&mx[i]); a[i]--; b[i]--; }
  for(i=0;i<(1<<(N-2));i++) {
    for(j=0;j<N-2;j++) st[j+1]=(i>>j)&1;
    st[0]=st[N-1]=1;
    t[0]=0;
    for(j=1;j<N;j++) t[j]=t[j-1]+s[j-1]/2+st[j-1]+st[j];
    tot=0;
    for(j=0;j<P;j++) if(st[a[j]] && st[b[j]] && t[b[j]]-t[a[j]]<=mx[j]) tot+=cs[b[j]]-cs[a[j]];
    if(tot>max) {
      max=tot;
      for(j=0;j<N;j++) bra[j]=st[j]?t[j]:-1;
    }
  }
  printf("%d\n", max);
  for(i=0;i<N;i++) if(bra[i]>=0) printf("%d %d\n", i+1,bra[i]);
  return 0;
}

    
