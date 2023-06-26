#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100000;
vector<I>cpss;
tuple<I,I,I>rngs[N];
Lli segs[4*N];
I cps(I x){
  return lower_bound(cpss.begin(),cpss.end(),x)-cpss.begin();
}
void upd(I i,Lli val){
  i+=cpss.size();
  for(segs[i]=max(segs[i],val);i>>=1;)segs[i]=max(segs[i<<1],segs[i<<1|1]);
}
Lli qry(I l,I r){
  Lli res=0;
  for(l+=cpss.size(),r+=cpss.size();l<r;l>>=1,r>>=1){
    if(l&1)res=max(res,segs[l++]);
    if(r&1)res=max(res,segs[--r]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I a,b,h;cin>>a>>b>>h;
    rngs[i]={b,a,h};
    cpss.push_back(a),cpss.push_back(b);
  }
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<n;i++){
    auto[b,a,h]=rngs[i];
    rngs[i]={cps(b),cps(a),h};
  }
  sort(rngs,rngs+n);
  reverse(rngs,rngs+n);
  for(I i=0;i<n;i++){
    auto[b,a,h]=rngs[i];
    upd(a,qry(0,b)+h);
  }
  printf("%lli\n",qry(0,cpss.size()));
}