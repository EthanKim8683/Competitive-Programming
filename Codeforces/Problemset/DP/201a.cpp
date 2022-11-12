#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=10;
const I X=100;

B dp[N][X+1][1<<N];
I x;
I n;

B yes(I v){
  for(I i=0;i+1<n;i++)if((v>>i&1)&&(v>>(i+1)&1))return 0;
  return 1;
}

B chk(I v){
  n=v;
  for(I i=0;i<n;i++)for(I j=0;j<=x;j++)for(I k=0;k<(1<<n);k++)dp[i][j][k]=0;
  for(I i=0;i<(1<<n);i++){
    if(!yes(i))continue;
    I m=2*__builtin_popcount(i)-1*(i&1);
    if(m>x)continue;
    dp[0][m][i]=1;
  }
  for(I i=0;i+1<n;i++)for(I j=0;j<=x;j++)for(I k=0;k<(1<<n);k++){
    if(!dp[i][j][k])continue;
    for(I l=0;l<(1<<n);l++){
      if(!yes(l))continue;
      if(l&k)continue;
      I m=j+4*__builtin_popcount(l)-2*(l&1);
      if(m>x)continue;
      dp[i+1][m][l]=1;
    }
  }
  return *max_element(dp[n-1][x],dp[n-1][x]+(1<<n));
}

I fnd(){
  I l=1,r=N;
  while(l<r){
    I m=l+(r-l)/2;
    if(chk(m))r=m;
    else l=m+1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>x;
  printf("%i\n",fnd()*2-1);
}