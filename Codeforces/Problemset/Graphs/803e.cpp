#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;
using C=char;

const I N=1000;
const I K=1000;

C toc[]{'L','D','W'};
B dp[N+1][K+K+1];
I pars[N+1][K+K+1];

void add(I i,I j,I k){
  dp[i+1][j+k-1]=1,pars[i+1][j+k-1]=k;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  S s;cin>>s;
  dp[0][K+0]=1;
  for(I i=0;i<n;i++){
    C c=s[i];
    for(I j=K-k+1;j<K+k;j++){
      if(!dp[i][j])continue;
      if(c=='L')add(i,j,0);
      if(c=='D')add(i,j,1);
      if(c=='W')add(i,j,2);
      if(c=='?')add(i,j,0),add(i,j,1),add(i,j,2);
    }
  }
  I j=-1;
  if(dp[n][K-k])j=K-k;
  if(dp[n][K+k])j=K+k;
  if(j==-1)printf("NO\n"),exit(0);
  for(I i=n;i>0;i--){
    I k=pars[i][j];
    s[i-1]=toc[k],j-=k-1;
  }
  printf("%s\n",s.c_str());
}