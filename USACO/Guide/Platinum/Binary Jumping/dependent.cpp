#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2e5;
const I LOGN=18;
const Lli MOD=1e9+7;
const Lli D=1e6;
const Lli INVD=142857001;
vector<I>adjs[N];
pair<Lli,Lli>prbs[N];
I sizs[N],tops[N];
I tbgs[N],teds[N];
I ancs[N][LOGN];
pair<Lli,Lli>segs[2*N];
I tim=0;
I n;
pair<Lli,Lli>cmb(pair<Lli,Lli>a,pair<Lli,Lli>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  return{x1*x2%MOD,(y1*x2+y2)%MOD};
}
void upd(I i,pair<Lli,Lli>x){
  for(segs[i+=n]=x;i>1;i>>=1)segs[i>>1]=cmb(segs[i&~1],segs[i|1]);
}
pair<Lli,Lli>qry(I l,I r){
  pair<Lli,Lli>lrs={1,0},rrs={1,0};
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)lrs=cmb(lrs,segs[l++]);
    if(r&1)rrs=cmb(segs[--r],rrs);
  }
  return cmb(lrs,rrs);
}
void dfs1(I a,I p){
  sizs[a]=1;
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  for(auto&b:adjs[a]){
    dfs1(b,a);
    sizs[a]+=sizs[b];
    if(sizs[b]>sizs[adjs[a][0]])swap(b,adjs[a][0]);
  }
}
void dfs2(I a){
  tbgs[a]=tim++;
  auto[x,y]=prbs[a];
  upd(tbgs[a],{(x-y)*INVD%MOD,y%MOD});
  for(auto b:adjs[a]){
    tops[b]=b==adjs[a][0]?tops[a]:b;
    dfs2(b);
  }
  teds[a]=tim;
}
pair<Lli,Lli>pte(I l,I u){
  pair<Lli,Lli>res={1,0};
  while(tops[l]!=tops[u]){
    res=cmb(qry(tbgs[tops[l]],tbgs[l]+1),res);
    l=ancs[tops[l]][0];
  }
  return cmb(qry(tbgs[u]+1,tbgs[l]+1),res);
}
pair<Lli,Lli>pti(I l,I u){
  return cmb(qry(tbgs[u],tbgs[u]+1),pte(l,u));
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
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  for(I i=1;i<=t;i++){
    I q;cin>>n>>q;
    for(I j=0;j<n;j++)adjs[j].clear();
    I k;cin>>k;
    prbs[0]={k,0};
    for(I j=1;j<n;j++){
      I p,a,b;cin>>p>>a>>b,p--;
      adjs[p].push_back(j);
      prbs[j]={a,b};
    }
    tim=0,dfs1(0,0),dfs2(0);
    printf("Case #%i:",i);
    while(q--){
      I u,v;cin>>u>>v,u--,v--;
      I x=lca(u,v);
      auto[x1,y1]=pte(u,x);
      auto[x2,y2]=pte(v,x);
      auto[x3,y3]=pti(x,0);
      Lli p3=(D*x3+y3)%MOD;
      Lli res1=1,res2=1;
      (res1*=(D*x1+y1)%MOD)%=MOD;
      (res1*=(D*x2+y2)%MOD)%=MOD;
      (res1*=p3)%=MOD;
      (res2*=(0*x1+y1)%MOD)%=MOD;
      (res2*=(0*x2+y2)%MOD)%=MOD;
      (res2*=D-p3)%=MOD;
      Lli res=(res1+res2)%MOD;
      (res*=INVD)%=MOD;
      (res*=INVD)%=MOD;
      (res*=INVD)%=MOD;
      printf(" %lli",res+(res<0)*MOD);
    }
    printf("\n");
  }
}