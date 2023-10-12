#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100;
const I M=100;
const Lli MAX=1e18;
Lli a_arr[N][M];
vector<Lli>cpss;
Lli dp[N][M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>a_arr[i][j];
    cpss.clear();
    for(I i=0;i<n;i++)for(I j=0;j<m;j++){
      Lli rep=a_arr[i][j]-i-j;
      if(rep<=a_arr[0][0])cpss.push_back(rep);
    }
    sort(cpss.begin(),cpss.end());
    cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
    Lli res=MAX;
    for(auto i:cpss){
      for(I j=0;j<n;j++)for(I k=0;k<m;k++)dp[j][k]=MAX;
      dp[0][0]=a_arr[0][0]-i;
      for(I j=0;j<n;j++)for(I k=0;k<m;k++){
        if(j+1<n){
          Lli cst=a_arr[j+1][k]-(i+j+1+k);
          if(cst>=0)dp[j+1][k]=min(dp[j+1][k],dp[j][k]+cst);
        }
        if(k+1<m){
          Lli cst=a_arr[j][k+1]-(i+j+k+1);
          if(cst>=0)dp[j][k+1]=min(dp[j][k+1],dp[j][k]+cst);
        }
      }
      res=min(res,dp[n-1][m-1]);
    }
    printf("%lli\n",res);
  }
}