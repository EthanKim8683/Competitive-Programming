#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const I N=3e5;

Lli dp[N][4];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  for(I i=0;i<n;i++)dp[i][(s[i]-'0')%4]+=1;
  for(I i=0;i+1<n;i++)for(I j=0;j<4;j++)dp[i+1][(j*10+s[i+1]-'0')%4]+=dp[i][j];
  Lli res=0;
  for(I i=0;i<n;i++)res+=dp[i][0];
  printf("%lli\n",res);
}