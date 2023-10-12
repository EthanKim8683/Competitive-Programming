#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const Lli MOD=1e9+7;
pair<I,I>rngs[N];
multiset<I>curs,bufs;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;Lli x,y;cin>>n>>x>>y;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r;
    rngs[i]={l,r};
  }
  sort(rngs,rngs+n);
  Lli res=0;
  for(I i=0;i<n;i++){
    auto[l,r]=rngs[i];
    while(bufs.size()){
      auto it=bufs.begin();
      if(*it>=l)break;
      curs.insert(*it);
      bufs.erase(it);
    }
    if(curs.size()){
      auto it=prev(curs.end());
      Lli cst=(l-*it)*y;
      (res+=min(cst,x))%=MOD;
      curs.erase(it);
    }else(res+=x)%=MOD;
    (res+=y*(r-l))%=MOD;
    bufs.insert(r);
  }
  printf("%lli\n",res);
}