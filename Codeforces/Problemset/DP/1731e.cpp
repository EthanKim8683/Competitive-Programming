#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e6;
I cons[N+1];
B coms[N+1];
Lli cops[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  iota(cops,cops+N+1,0);
  fill_n(cons,N+1,1);
  cops[1]=0;
  for(I i=2;i*i<=N;i++)if(!coms[i]){
    for(I j=i*i;j<=N;j+=i)coms[j]=1;
    for(I j=i*i;j<=N;j*=i)for(I k=j;k<=N;k+=j)cons[k]=0;
  }
  for(I i=2;i<=N;i++){
    if(!coms[i])for(I j=i;j<=N;j+=i)cons[j]*=-1;
    for(I j=1;i*j<=N;j++)cops[i*j]+=cons[i]*j;
  }
  for(I i=1;i+1<=N;i++)cops[i+1]+=cops[i];
  I t;cin>>t;
  while(t--){
    I n;Lli m;cin>>n>>m;
    Lli res=0;
    for(I i=n;i>=2;i--){
      Lli cnt=min(m,cops[n/i])/(i-1);
      res+=cnt*i,m-=cnt*(i-1);
    }
    printf("%lli\n",m?-1:res);
  }
}