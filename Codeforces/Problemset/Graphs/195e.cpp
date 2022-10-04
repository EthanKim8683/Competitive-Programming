#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;
const Lli MOD=1e9+7;

I pars[N];
vector<I>adjs[N];
I inds[N];
vector<tuple<I,I,I,I>>edgs;
Lli segs[2*N];
I tbegs[N];
I tends[N];
I t=0;

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void dfs(I a){
  tbegs[a]=t++;
  for(auto b:adjs[a])dfs(b);
  tends[a]=t;
}

Lli qry(I i){
  Lli res=0;
  for(i+=t;i>0;i>>=1)(res+=segs[i])%=MOD;
  return res;
}

void upd(I l,I r,Lli val){
  val%=MOD;
  for(l+=t,r+=t;l<r;l>>=1,r>>=1){
    if(l&1)(segs[l++]+=val)%=MOD;
    if(r&1)(segs[--r]+=val)%=MOD;
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(pars,n,-1);
  for(I i=0;i<n;i++){
    I k;cin>>k;
    for(I j=0;j<k;j++){
      I v,x;cin>>v>>x,v--;
      adjs[i].push_back(fnd(v));
      edgs.push_back({i,fnd(v),v,x});
      inds[fnd(v)]++;
      pars[fnd(v)]=i;
    }
  }
  for(I i=0;i<n;i++)if(!inds[i])dfs(i);
  Lli res=0;
  for(auto[c,a,b,x]:edgs){
    (res+=qry(tbegs[b])+x)%=MOD;
    upd(tbegs[a],tends[a],qry(tbegs[b])+x);
  }
  printf("%lli\n",(res+MOD)%MOD);
}