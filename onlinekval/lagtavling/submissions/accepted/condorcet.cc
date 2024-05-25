#include <stdio.h>

int main() {
  char inp[1001];
  int n[26],s[26],w[26],i,j,a,b,t,N,K;
  scanf("%d %d", &N,&K);
  scanf("%s", inp);
  for(i=0;i<26;i++) w[i]=0;
  for(a=0;a<26;a++) 
    for(b=a+1;b<26;b++) {
        n[a]=s[a]=n[b]=s[b]=0;
	for(i=0,j=1;i<N;i++) {
	  t=inp[i]-'A';
	  if(t==a || t==b) {
	    n[t]++;
	    if(n[t]<=K) s[t]+=j;
	    j++;
	  }
	}
	if(n[a]>=K && (n[b]<K || s[a]<s[b])) w[a]++;
	if(n[b]>=K && (n[a]<K || s[b]<s[a])) w[b]++;
    }
  for(i=0;i<26;i++) if(w[i]==25) {
      printf("%c\n", i+'A');
      return 0;
    }
  printf("Ingen\n");
}
