#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=200000;
const I LOGN=18;
const Lli MOD=998244353;
pair<Lli,Lli>funs[N];
vector<I>adjs[N];
pair<Lli,Lli>segs1[2*N];
pair<Lli,Lli>segs2[2*N];
I ancs[N][LOGN];
I tbgs[N],teds[N];
I tops[N],sizs[N];
I tim=0;
I n;
pair<Lli,Lli>cmb1(pair<Lli,Lli>a,pair<Lli,Lli>b){
  auto[a1,b1]=a;auto[a2,b2]=b;
  return{a1*a2%MOD,(b1*a2+b2)%MOD};
}
pair<Lli,Lli>cmb2(pair<Lli,Lli>a,pair<Lli,Lli>b){
  auto[a1,b1]=a;auto[a2,b2]=b;
  return{a2*a1%MOD,(b2*a1+b1)%MOD};
}
void upd(I i,pair<Lli,Lli>x){
  for(segs1[i+=n]=x,segs2[i]=x;i>1;i>>=1){
    segs1[i>>1]=cmb1(segs1[i&~1],segs1[i|1]);
    segs2[i>>1]=cmb2(segs2[i&~1],segs2[i|1]);
  }
}
pair<Lli,Lli>qry1(I l,I r){
  pair<Lli,Lli>lrs={1,0},rrs={1,0};
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)lrs=cmb1(lrs,segs1[l++]);
    if(r&1)rrs=cmb1(segs1[--r],rrs);
  }
  return cmb1(lrs,rrs);
}
pair<Lli,Lli>qry2(I l,I r){
  pair<Lli,Lli>lrs={1,0},rrs={1,0};
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)lrs=cmb2(lrs,segs2[l++]);
    if(r&1)rrs=cmb2(segs2[--r],rrs);
  }
  return cmb2(lrs,rrs);
}
void dfs1(I a,I p){
  sizs[a]=1;
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  for(auto&b:adjs[a])if(b!=p){
    dfs1(b,a);
    sizs[a]+=sizs[b];
    if(sizs[b]>sizs[adjs[a][0]])swap(b,adjs[a][0]);
  }
}
void dfs2(I a,I p=-1){
  tbgs[a]=tim++;
  upd(tbgs[a],funs[a]);
  for(auto b:adjs[a])if(b!=p){
    tops[b]=b==adjs[a][0]?tops[a]:b;
    dfs2(b,a);
  }
  teds[a]=tim;
}
B anc(I a,I b){
  return tbgs[a]<=tbgs[b]&&teds[a]>=teds[b];
}
I lca(I a,I b){
  if(anc(a,b))return a;
  if(anc(b,a))return b;
  for(I i=LOGN-1;i>=0;i--)if(!anc(ancs[a][i],b))a=ancs[a][i];
  return ancs[a][0];
}
pair<Lli,Lli>pat1(I u,I v){
  pair<Lli,Lli>res={1,0};
  for(;tops[u]!=tops[v];u=ancs[tops[u]][0])res=cmb1(qry1(tbgs[tops[u]],tbgs[u]+1),res);
  return cmb1(qry1(tbgs[v]+1,tbgs[u]+1),res);
}
pair<Lli,Lli>pat2(I u,I v){
  pair<Lli,Lli>res={1,0};
  for(;tops[u]!=tops[v];u=ancs[tops[u]][0])res=cmb2(qry2(tbgs[tops[u]],tbgs[u]+1),res);
  return cmb2(qry2(tbgs[v]+1,tbgs[u]+1),res);
}
Lli pat(I u,I v,Lli x){
  I t=lca(u,v);
  auto[a,b]=cmb1(cmb1(pat2(u,t),funs[t]),pat1(v,t));
  return(x*a+b)%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>n>>q;
  for(I i=0;i<n;i++){
    I a,b;cin>>a>>b;
    funs[i]={a,b};
  }
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  dfs1(0,0),dfs2(0);
  while(q--){
    I t;cin>>t;
    if(t==0){
      I p,c,d;cin>>p>>c>>d;
      upd(tbgs[p],funs[p]={c,d});
    }
    if(t==1){
      I u,v,x;cin>>u>>v>>x;
      printf("%lli\n",pat(u,v,x));
    }
  }
}