#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using C=char;
using B=bool;

const I N=10;
const I M=10;

S a_arr[N];
pair<I,I>dp[M+1][1<<N];
I difs[M][26];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<=m;i++)for(I j=0;j<(1<<n);j++)dp[i][j].first=-1;
    for(I i=0;i<m;i++)for(I j=0;j<26;j++){
      I msk=0;
      for(I k=0;k<n;k++)msk|=(a_arr[k][i]!=j+'a')<<k;
      difs[i][j]=msk;
    }
    dp[0][0].first=0;
    for(I i=0;i<m;i++){
      for(I j=0;j<(1<<n);j++){
        if(dp[i][j].first==-1)continue;
        for(I k=0;k<26;k++){
          I msk=difs[i][k];
          if(!(j&msk))dp[i+1][j|msk]={j,k};
        }
      }
    }
    I j=-1;
    for(I i=0;i<(1<<n);i++)if(dp[m][i].first!=-1)j=i;
    if(j==-1){printf("-1\n");continue;}
    S res="";
    for(I i=m;i>0;i--){
      auto[k,l]=dp[i][j];
      res=S(1,l+'a')+res;
      j=k;
    }
    printf("%s\n",res.c_str());
  }
}