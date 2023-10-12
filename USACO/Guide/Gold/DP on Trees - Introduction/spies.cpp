#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1000000;
const I MIN=-1e9;
I a_arr[N];
I viss[N];
B cuts[N];
I tops[N];
I dp1[N][2],dp2[2][2][2];
I t=0;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I a;cin>>a,a--;
    a_arr[i]=a;
  }
  I l=n;
  for(I i=0;i<n;i++){
    dp1[i][1]=MIN;
    I r=l,j=i;
    for(;viss[j]==0;j=a_arr[j])tops[--l]=j,viss[j]=1;
    if(viss[j]==1)for(;!cuts[j];j=a_arr[j])cuts[j]=1;
    for(I j=i;viss[j]!=2;j=a_arr[j])viss[j]=2;
    reverse(tops+l,tops+r);
  }
  for(I i=0;i<n;i++){
    I a=tops[i];
    dp1[a][1]+=dp1[a][0]+1;
    if(cuts[a])continue;
    I b=b=a_arr[a];
    dp1[b][0]+=max(dp1[a][0],dp1[a][1]);
    dp1[b][1]=max(dp1[b][1],dp1[a][0]-max(dp1[a][0],dp1[a][1]));
  }
  fill_n(viss,n,0);
  I res=0;
  for(I i=0;i<n;i++){
    I j=i;
    for(;viss[j]==0;j=a_arr[j])viss[j]=1;
    if(viss[j]==1){
      dp2[0][1][1]=dp2[0][0][0]=0;
      dp2[0][0][1]=dp2[0][1][0]=MIN;
      I t=1;
      for(I k=a_arr[j];k!=j;k=a_arr[k],t=!t)for(I l=0;l<2;l++){
        dp2[t][l][1]=max(dp2[!t][l][0]+dp1[k][0]+1,dp2[!t][l][1]+dp1[k][1]);
        dp2[t][l][0]=max(dp2[!t][l][0],dp2[!t][l][1])+dp1[k][0];
      }
      I cur=0;
      cur=max(cur,max(dp2[!t][1][0]+dp1[j][0]+1,dp2[!t][1][1]+dp1[j][1]));
      cur=max(cur,max(dp2[!t][0][0],dp2[!t][0][1])+dp1[j][0]);
      res+=cur;
    }
    for(I j=i;viss[j]!=2;j=a_arr[j])viss[j]=2;
  }
  printf("%i\n",res);
}