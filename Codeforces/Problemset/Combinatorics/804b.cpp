#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
using C=char;
const Lli MOD=1e9+7;
vector<pair<C,I>>rngs;
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size(),l=0;
  for(I r=0;r<n;r++)if(s[r]!=s[l])rngs.push_back({s[l],r-l}),l=r;
  rngs.push_back({s[l],n-l});
  Lli res=0;
  for(I i=0;i+1<rngs.size();i++)if(rngs[i].first=='a'){
    (res+=rngs[i+1].second*(mpw(2,rngs[i].second)-1))%=MOD;
    if(i+2<rngs.size())rngs[i+2].second+=rngs[i].second;
  }
  printf("%lli\n",(res+MOD)%MOD);
}