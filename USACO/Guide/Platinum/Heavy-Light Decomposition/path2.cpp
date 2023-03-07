#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
I v_arr[N];
vector<I>adjs[N];
I sizs[N];
I pars[N];
I deps[N];
I tops[N];
I inds[N];
I segs[2*N];
I t=0;
I n;
void upd(I i,I x){
  for(segs[i+=n]=x;i>1;i>>=1)segs[i>>1]=max(segs[i],segs[i^1]);
}
I qry(I l,I r){
  I res=0;
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)res=max(res,segs[l++]);
    if(r&1)res=max(res,segs[--r]);
  }
  return res;
}
I dfs1(I a,I p){
  sizs[a]=1,pars[a]=p;
  for(auto&b:adjs[a])if(b!=p){
    deps[b]=deps[a]+1;
    sizs[a]+=dfs1(b,a);
    if(sizs[b]>sizs[adjs[a][0]])swap(b,adjs[a][0]);
  }
  return sizs[a];
}
void dfs2(I a,I p){
  upd(inds[a]=t++,v_arr[a]);
  for(auto b:adjs[a])if(b!=p){
    tops[b]=b==adjs[a][0]?tops[a]:b;
    dfs2(b,a);
  }
}
I pat(I a,I b){
  I res=0;
  for(;tops[a]!=tops[b];a=pars[tops[a]]){
    if(deps[tops[a]]<deps[tops[b]])swap(a,b);
    res=max(res,qry(inds[tops[a]],inds[a]+1));
  }
  if(deps[a]>deps[b])swap(a,b);
  return max(res,qry(inds[a],inds[b]+1));
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>v_arr[i];
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs1(0,0),dfs2(0,0);
  while(q--){
    I t;cin>>t;
    if(t==1){
      I s,x;cin>>s>>x,s--;
      upd(inds[s],v_arr[s]=x);
    }
    if(t==2){
      I a,b;cin>>a>>b,a--,b--;
      printf("%i ",pat(a,b));
    }
  }
}