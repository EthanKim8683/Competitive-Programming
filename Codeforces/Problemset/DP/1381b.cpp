#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=2000;

I p_arr[2*N];
I dp1[2*N];
B dp2[2*N+1][2*N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<2*n;i++)cin>>p_arr[i];
    for(I i=0;i<2*n;i++){
      dp1[i]=-1;
      for(I j=2*n-1;j>i;j--)if(p_arr[j]>p_arr[i])dp1[i]=j;
    }
    for(I i=0;i<=2*n;i++)for(I j=0;j<=2*n;j++)dp2[i][j]=0;
    dp2[0][0]=1;
    for(I i=0;i<2*n;i++)for(I j=0;j<=2*n;j++){
      if(!dp2[i][j])continue;
      I k=dp1[i];
      dp2[2*n][2*n-i+j]=1;
      if(k!=-1){
        dp2[k][k-i+j]=1;
        dp2[k][k-(k-i+j)]=1;
      }
    }
    printf("%s\n",dp2[2*n][n]?"YES":"NO");
  }
}