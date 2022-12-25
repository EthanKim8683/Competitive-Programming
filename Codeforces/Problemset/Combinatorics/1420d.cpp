#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3e5;
const Lli MOD=998244353;
pair<I,I>rngs[N];
vector<I>cpss;
I ps[2*N+1];
Lli facs[N+1];
I cps(I x){
  return lower_bound(cpss.begin(),cpss.end(),x)-cpss.begin();
}
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  if(n<0||k<0||n-k<0)return 0;
  return facs[n]*inv(facs[n-k]*facs[k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r;
    rngs[i]={l,r};
  }
  facs[0]=1;
  for(I i=1;i<=n;i++)facs[i]=facs[i-1]*i%MOD;
  for(I i=0;i<n;i++){
    auto[l,r]=rngs[i];
    cpss.push_back(l);
    cpss.push_back(r);
  }
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<n;i++){
    auto[l,r]=rngs[i];
    rngs[i]={cps(l),cps(r)};
  }
  for(I i=0;i<n;i++){
    auto[l,r]=rngs[i];
    ps[l]++,ps[r+1]--;
  }
  for(I i=0;i+1<cpss.size();i++)ps[i+1]+=ps[i];
  Lli res=0;
  for(I i=0;i<n;i++){
    auto[l,r]=rngs[i];
    (res+=bin(--ps[l],k-1))%=MOD;
  }
  printf("%lli\n",res);
}