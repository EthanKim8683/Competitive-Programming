#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=1e6;
const Lli MOD=1e9+7;
Lli dp[N+1][5];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  if(s[0]=='*'||s[0]=='?')dp[1][0]=1;
  if(s[0]=='0'||s[0]=='?')dp[1][1]=1;
  if(s[0]=='1'||s[0]=='?')dp[1][3]=1;
  if(s[0]=='2')printf("0\n"),exit(0);
  for(I i=1;i<n;i++){
    if(s[i]=='*'||s[i]=='?'){
      (dp[i+1][0]+=dp[i][0])%=MOD;
      (dp[i+1][0]+=dp[i][3])%=MOD;
      (dp[i+1][0]+=dp[i][4])%=MOD;
    }
    if(s[i]=='0'||s[i]=='?'){
      (dp[i+1][1]+=dp[i][1])%=MOD;
      (dp[i+1][1]+=dp[i][2])%=MOD;
    }
    if(s[i]=='1'||s[i]=='?'){
      (dp[i+1][2]+=dp[i][0])%=MOD;
      (dp[i+1][3]+=dp[i][1])%=MOD;
      (dp[i+1][3]+=dp[i][2])%=MOD;
    }
    if(s[i]=='2'||s[i]=='?'){
      (dp[i+1][4]+=dp[i][0])%=MOD;
    }
  }
  Lli res=0;
  (res+=dp[n][0])%=MOD;
  (res+=dp[n][1])%=MOD;
  (res+=dp[n][2])%=MOD;
  printf("%lli\n",res);
}