#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2e5;
const I LOGN=18;
vector<pair<I,I>>adjs[N];
I w_arr[N-1];
I bots[N-1];
I tbgs[N],teds[N];
Lli segs[2*N];
I ancs[N][LOGN+1];
I t=0;
I n;
void asn(I i,Lli val){
  segs[i+n]=val;
}
void upd(I l,I r,Lli val){
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)segs[l++]+=val;
    if(r&1)segs[--r]+=val;
  }
}
Lli qry(I i){
  Lli res=0;
  for(i+=n;i>0;i>>=1)res+=segs[i];
  return res;
}
void dfs(I a,I p,Lli d=0){
  ancs[a][0]=p;
  for(I i=1;i<=LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  asn(t,d);
  tbgs[a]=t++;
  for(auto[b,i]:adjs[a])if(b!=p)bots[i]=b,dfs(b,a,d+w_arr[i]);
  teds[a]=t;
}
B anc(I a,I b){
  return tbgs[a]<=tbgs[b]&&teds[a]>=teds[b];
}
I lca(I a,I b){
  if(anc(a,b))return a;
  if(anc(b,a))return b;
  for(I i=LOGN;i>=0;i--)if(!anc(ancs[a][i],b))a=ancs[a][i];
  return ancs[a][0];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n-1;i++){
    I u,v,w;cin>>u>>v>>w,u--,v--;
    adjs[u].push_back({v,i});
    adjs[v].push_back({u,i});
    w_arr[i]=w;
  }
  dfs(0,0);
  I q;cin>>q;
  while(q--){
    I t;cin>>t;
    if(t==1){
      I i,w;cin>>i>>w,i--;
      I j=bots[i];
      upd(tbgs[j],teds[j],w-w_arr[i]),w_arr[i]=w;
    }
    if(t==2){
      I u,v;cin>>u>>v,u--,v--;
      printf("%lli\n",qry(tbgs[u])+qry(tbgs[v])-2*qry(tbgs[lca(u,v)]));
    }
  }
}