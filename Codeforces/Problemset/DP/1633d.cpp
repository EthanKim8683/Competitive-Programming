#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e3;
const I B=1e3;
const I X=12;
const I MAX=1e9;
const I MIN=-1e9;

I b_arr[N];
I c_arr[N];
I dp1[B+1];
I dp2[N+1][N*X+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill_n(dp1,B+1,MAX);
  dp1[1]=0;
  for(I i=1;i<=B;i++)for(I j=1;j<=i;j++)
    if(i+i/j<=B)dp1[i+i/j]=min(dp1[i+i/j],dp1[i]+1);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>b_arr[i];
    for(I i=0;i<n;i++)cin>>c_arr[i];
    for(I i=0;i<=n;i++)for(I j=0;j<=n*X;j++)dp2[i][j]=MIN;
    dp2[0][0]=0;
    for(I i=0;i<n;i++)for(I j=0;j<=i*X;j++){
      I k=j+dp1[b_arr[i]],c=c_arr[i];
      dp2[i+1][j]=max(dp2[i+1][j],dp2[i][j]);
      dp2[i+1][k]=max(dp2[i+1][k],dp2[i][j]+c);
    }
    I res=MIN;
    for(I i=0;i<=min(n*X,k);i++)res=max(res,dp2[n][i]);
    printf("%i\n",res);
  }
}