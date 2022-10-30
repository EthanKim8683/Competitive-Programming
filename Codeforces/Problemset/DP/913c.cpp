#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=30;
const I L=31;
const Lli MAX=1e18;

I c_arr[N];
Lli dp1[L];
Lli dp2[L+1][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill_n(dp1,L,MAX);
  fill(&dp2[0][0],&dp2[0][0]+(L+1)*2,MAX);
  I n,l;cin>>n>>l;
  for(I i=0;i<n;i++)cin>>c_arr[i];
  copy_n(c_arr,n,dp1);
  for(I i=0;i<L;i++)for(I j=1;i+j<L;j++)
    dp1[i+j]=min(dp1[i+j],dp1[i]*(1<<j));
  dp2[L][0]=0;
  for(I i=L-1;i>=0;i--){
    I d=l>>i&1;
    if(d==1){
      dp2[i][1]=min(dp2[i][1],dp2[i+1][1]);
      dp2[i][0]=min(dp2[i][0],dp2[i+1][0]+dp1[i]);
    }
    if(d==0){
      dp2[i][1]=min(dp2[i][1],dp2[i+1][1]);
      dp2[i][1]=min(dp2[i][1],dp2[i+1][0]+dp1[i]);
      dp2[i][0]=min(dp2[i][0],dp2[i+1][0]);
    }
  }
  printf("%lli\n",min(dp2[0][0],dp2[0][1]));
}