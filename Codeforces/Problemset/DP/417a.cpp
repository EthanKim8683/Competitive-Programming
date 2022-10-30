#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100;
const I M=100;
const I MAX=1e9;

I dp[N*M+1];

void cmb(I&a,I b){
  a=min(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I c,d;cin>>c>>d;
  I n,m;cin>>n>>m;
  I k;cin>>k;
  I low=max(n*m-k,0),upp=low+n;
  fill_n(dp,upp+1,MAX);
  dp[0]=0;
  for(I i=0;i<upp;i++){
    if(i+n<=upp)cmb(dp[i+n],dp[i]+c);
    if(i+1<=upp)cmb(dp[i+1],dp[i]+d);
  }
  I res=MAX;
  for(I i=low;i<=upp;i++)res=min(res,dp[i]);
  printf("%i\n",res);
}