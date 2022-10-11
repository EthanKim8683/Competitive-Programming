#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using S=string;
using Lli=long long int;

const I N=4e4;
const Lli MOD=1e9+7;

vector<I>pals;
Lli dp[N+1];

B pal(I x){
  S t=to_string(x);
  for(I l=0,r=t.size()-1;l<r;l++,r--)if(t[l]!=t[r])return 0;
  return 1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  dp[0]=1;
  for(I i=1;i<=N;i++)if(pal(i))for(I j=0;j+i<=N;j++)(dp[j+i]+=dp[j])%=MOD;
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    printf("%lli\n",dp[n]);
  }
}