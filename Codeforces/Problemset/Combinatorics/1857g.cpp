#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const Lli MOD=998244353;
tuple<I,I,I>edgs[N-1];
I pars[N];
map<I,Lli>cnts;
I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}
void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}
I siz(I i){
  return-pars[fnd(i)];
}
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,s;cin>>n>>s;
    for(I i=0;i<n-1;i++){
      I u,v,w;cin>>u>>v>>w,u--,v--;
      edgs[i]={w,u,v};
    }
    cnts.clear();
    sort(edgs,edgs+n-1);
    fill_n(pars,n,-1);
    for(I i=0;i<n-1;i++){
      auto[w,u,v]=edgs[i];
      cnts[w]+=(Lli)siz(u)*siz(v)-1;
      uni(u,v);
    }
    Lli res=1;
    for(auto[w,cnt]:cnts)(res*=mpw(s-w+1,cnt))%=MOD;
    printf("%lli\n",res);
  }
}
/*
to construct a graph satisfying the provided conditions, we can start with the
given tree and add edges

we can add an edge of weight w between two different non-adjacent nodes a, b if
w is strictly greater than every edge on the path from a to b, but does not
exceed S

this is because we could otherwise cut the greatest edge from a to b and
replace it with the edge of weight w and still maintain connectivity

we can use Kruskal's to count, for each edge weight w, the number of pairs of
non-adjacent nodes whose path has maximum weight equal to w

then, we can take the product of the contribution of each w, equal to
(S - w + 1) ^ c, where c is the aforementioned number of pairs for w
*/