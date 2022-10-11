#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I K=200;
const I N=200;

B dp[K+1][N+1];
I pars[K+1][N+1];
I lens[K];
I n;

void add(I i,I j,I k){
  if(!dp[i][j])return;
  if(j+k>n)return;
  if(dp[i+1][j+k])return;
  dp[i+1][j+k]=1,pars[i+1][j+k]=k;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k,a,b;cin>>k>>a>>b;
  S s;cin>>s;
  n=s.size();
  dp[0][0]=1;
  for(I i=0;i<k;i++)for(I j=0;j<=n;j++)for(I k=a;k<=b;k++)add(i,j,k);
  if(!dp[k][n])printf("No solution\n"),exit(0);
  I j=n;
  for(I i=k;i>0;i--){
    I p=pars[i][j];
    lens[i-1]=p,j-=p;
  }
  I l=0;
  for(I i=0;i<k;i++){
    I len=lens[i];
    printf("%s\n",s.substr(l,len).c_str());
    l+=len;
  }
}