#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=2e5;
const I MAX=1e9;
const I MIN=-1e9;

I x_arr[N];
I cnts[N];
I dp1[N+1][2][2];
I dp2[N+1][2][2];

void cmb1(I&a,I b){
  a=min(a,b);
}

void cmb2(I&a,I b){
  a=max(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp1[0][0][0],&dp1[0][0][0]+(N+1)*2*2,MAX);
  fill(&dp2[0][0][0],&dp2[0][0][0]+(N+1)*2*2,MIN);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  for(I i=0;i<n;i++)cnts[x_arr[i]-1]++;
  dp1[0][0][0]=dp2[0][0][0]=0;
  for(I i=0;i<n;i++)for(I j=0;j<2;j++)for(I k=0;k<2;k++){
    I cnt=min(cnts[i],3);
    if(cnt==0){
      cmb1(dp1[i+1][0][j],dp1[i][j][k]);
      cmb2(dp2[i+1][0][j],dp2[i][j][k]);
      continue;
    }
    for(I l=1;l<(1<<3);l++){
      if(__builtin_popcount(l)>cnt)continue;
      I a=0|l>>0&1,b=j|l>>1&1,c=k|l>>2&1;
      I cst=(a!=0)+(b!=j)+(c!=k);
      cmb1(dp1[i+1][a][b],dp1[i][j][k]+cst);
      cmb2(dp2[i+1][a][b],dp2[i][j][k]+cst);
    }
  }
  I res1=MAX,res2=MIN;
  for(I i=0;i<2;i++)for(I j=0;j<2;j++){
    cmb1(res1,dp1[n][i][j]);
    cmb2(res2,dp2[n][i][j]);
  }
  printf("%i %i\n",res1,res2);
}