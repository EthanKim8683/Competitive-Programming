#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200000;
const Lli MOD=1e9+7;
Lli facs[N+1];
pair<I,I>segs[N];
vector<I>cpss;
I sizs[2*N-1];
I ps[2*N];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  if(n<k)return 0;
  return facs[n]*inv(facs[n-k]*facs[k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r;
    segs[i]={l,r};
  }
  facs[0]=1;
  for(I i=1;i<=n;i++)facs[i]=facs[i-1]*i%MOD;
  for(I i=0;i<n;i++){
    auto[l,r]=segs[i];
    cpss.push_back(l);
    cpss.push_back(r+1);
  }
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i+1<cpss.size();i++)sizs[i]=cpss[i+1]-cpss[i];
  for(I i=0;i<n;i++){
    auto[l,r]=segs[i];
    l=lower_bound(cpss.begin(),cpss.end(),l)-cpss.begin();
    r=lower_bound(cpss.begin(),cpss.end(),r+1)-cpss.begin();
    ps[l]++,ps[r]--;
  }
  for(I i=0;i<cpss.size();i++)ps[i+1]+=ps[i];
  Lli res=0;
  for(I i=0;i+1<cpss.size();i++)(res+=bin(ps[i],k)*sizs[i])%=MOD;
  printf("%lli\n",res);
}