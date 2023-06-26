#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const Lli MOD=1e9+7;
Lli dp[3+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  dp[0]=1;
  for(I i=0;i<n;i++){
    if(s[i]=='?'){
      (dp[3]*=3)%=MOD;
      (dp[3]+=dp[2])%=MOD;
      (dp[2]*=3)%=MOD;
      (dp[2]+=dp[1])%=MOD;
      (dp[1]*=3)%=MOD;
      (dp[1]+=dp[0])%=MOD;
      (dp[0]*=3)%=MOD;
    }
    if(s[i]=='a')(dp[1]+=dp[0])%=MOD;
    if(s[i]=='b')(dp[2]+=dp[1])%=MOD;
    if(s[i]=='c')(dp[3]+=dp[2])%=MOD;
  }
  printf("%lli\n",dp[3]);
}