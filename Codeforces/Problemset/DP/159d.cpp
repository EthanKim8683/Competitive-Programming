#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const I N=2000;

I dp[N][N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  for(I i=0;i<n;i++){
    for(I j=0;j+i<n;j++){
      if(s[j]!=s[j+i])continue;
      if(i<=1){dp[j][j+i]=1;continue;}
      dp[j][j+i]=dp[j+1][j+i-1];
    }
  }
  Lli cnt=0,res=0;
  for(I i=0;i<n;i++){
    for(I j=0;i+j<n;j++)res+=cnt*dp[i][i+j];
    for(I j=0;j<=i;j++)cnt+=dp[i-j][i];
  }
  printf("%lli\n",res);
}