#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=5000;
const Lli MOD=1e9+7;
I c_arr[N];
Lli dp1[N+1][N+1],dp2[N+1];
B viss1[N+1][N+1],viss2[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>c_arr[i];
    for(I i=0;i<=n;i++){
      for(I j=0;j<=n;j++)dp1[i][j]=0,viss1[i][j]=0;
      dp2[i]=0,viss2[i]=0;
    }
    dp1[0][0]=1,viss1[0][0]=1;
    dp2[0]=1,viss2[0]=1;
    for(I i=0;i<n;i++)for(I j=i;j>=0;j--){
      I c=c_arr[i];
      if(j%k==0){
        (dp1[j+1][c]+=dp2[j])%=MOD,viss1[j+1][c]|=viss2[j];
        (dp2[j+1]+=dp2[j])%=MOD,viss2[j+1]|=viss2[j];
      }else{
        (dp1[j+1][c]+=dp1[j][c])%=MOD,viss1[j+1][c]|=viss1[j][c];
        (dp2[j+1]+=dp1[j][c])%=MOD,viss2[j+1]|=viss1[j][c];
      }
    }
    Lli res=0;
    for(I i=n/k*k;i>=0;i-=k){
      (res+=dp2[i])%=MOD;
      if(viss2[i])break;
    }
    printf("%lli\n",res);
  }
}
/*
we can use dynamic programming on index, length and color
*/