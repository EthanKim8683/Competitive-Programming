#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using S=string;
const I N=100;
const Lli MOD=1e9+7;
Lli dp[N*26+1][N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  dp[0][0]=1;
  for(I i=0;i<N*26;i++)for(I j=0;j<N;j++)for(I k=1;k<=26&&i+k<=N*26;k++)(dp[i+k][j+1]+=dp[i][j])%=MOD;
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I sum=0;
    for(auto c:s)sum+=c-'a'+1;
    printf("%lli\n",(dp[sum][s.size()]-1+MOD)%MOD);
  }
}