#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;
using Lli=long long int;

const I K=1e5;
const Lli MOD=1e9+7;

Lli dp[K+1][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S a;cin>>a;
  S b;cin>>b;
  I k;cin>>k;
  I n=a.size();
  dp[0][0]=1;
  for(I i=0;i<k;i++){
    (dp[i+1][1]+=dp[i][1]*(n-2)+dp[i][0])%=MOD;
    (dp[i+1][0]+=dp[i][1]*(n-1))%=MOD;
  }
  S t=a;
  Lli res=0;
  for(I i=0;i<n;i++){
    if(t==b)(res+=dp[k][i!=0])%=MOD;
    t=t.substr(1)+t[0];
  }
  printf("%lli\n",res);
}