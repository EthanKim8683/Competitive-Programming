#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I M=1e5;
const Lli MOD=1e9+7;

pair<I,I>buss[M];
vector<I>cpss;
vector<I>begs[2*M+1];
Lli ps[2*M+2];
Lli dp[2*M+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  cpss.push_back(0);
  cpss.push_back(n);
  for(I i=0;i<m;i++){
    I s,t;cin>>s>>t;
    buss[i]={s,t};
    cpss.push_back(t);
  }
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  n=lower_bound(cpss.begin(),cpss.end(),n)-cpss.begin();
  dp[0]=1;
  for(I i=0;i<m;i++){
    auto[s,t]=buss[i];
    s=lower_bound(cpss.begin(),cpss.end(),s)-cpss.begin();
    t=lower_bound(cpss.begin(),cpss.end(),t)-cpss.begin();
    begs[t].push_back(s);
  }
  for(I i=0;i<cpss.size();i++){
    for(auto j:begs[i])(dp[i]+=ps[i]-ps[j])%=MOD;
    (ps[i+1]=dp[i]+ps[i])%=MOD;
  }
  printf("%lli\n",(dp[n]+MOD)%MOD);
}