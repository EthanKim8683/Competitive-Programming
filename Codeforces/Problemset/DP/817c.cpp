#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using S=string;

const I L=19;

Lli dp[L+1][L*9+1];

Lli slv(Lli x,I y){
  S s=to_string(x);
  I l=s.size();
  for(I i=0;i<=l;i++)for(I j=0;j<=y;j++)dp[i][j]=0;
  I sum=0;
  for(I i=0;i<l;i++){
    I d=s[i]-'0';
    for(I j=0;j<d;j++)dp[i+1][sum+j]+=1;
    sum+=d;
    for(I j=0;j<=y;j++)for(I k=0;k<10&&j+k<=y;k++)dp[i+1][j+k]+=dp[i][j];
  }
  return dp[l][y];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli n,s;cin>>n>>s;
  Lli res=0;
  for(I i=0;i<=L*9;i++)res+=max(slv(n+1,i)-slv(i+s,i),(Lli)0);
  printf("%lli\n",res);
}