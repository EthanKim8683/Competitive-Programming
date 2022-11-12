#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1000;
const I H=1000;
const Lli MAX=1e18;

pair<I,I>frds[N];

Lli dp[N+1][H+1];

void cmb(Lli&a,Lli b){
  a=min(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*(H+1),MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I w,h;cin>>w>>h;
    frds[i]={w,h};
  }
  dp[0][0]=0;
  for(I i=0;i<n;i++)for(I j=0;j<=H;j++){
    auto[w,h]=frds[i];
    cmb(dp[i+1][max(j,w)],dp[i][j]+h);
    cmb(dp[i+1][max(j,h)],dp[i][j]+w);
  }
  Lli res=MAX;
  for(I i=0;i<=H;i++){
    Lli w=dp[n][i];
    if(w==MAX)continue;
    res=min(res,i*w);
  }
  printf("%lli\n",res);
}