#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=150000;
const Lli MOD=998244353;
vector<I>adjs[N];
tuple<Lli,Lli,I>segs1[2*N];
Lli segs2[2*N];
I sizs[N],tops[N],pars[N];
I tbgs[N],teds[N];
I tim=0;
I n;
tuple<Lli,Lli,I>cmb1(tuple<Lli,Lli,I>a,tuple<Lli,Lli,I>b){
  auto[t1,r1,i1]=a;auto[t2,r2,i2]=b;
  if(i1==-1)return b;
  if(i2==-1)return a;
  return{(t1+t2+r1*sizs[i2])%MOD,r2,i1};
}
void asn(I i,I j){
  segs1[i+n]={0,0,j};
}
void bld1(){
  for(I i=n-1;i>0;i--)segs1[i]=cmb1(segs1[i<<1],segs1[i<<1|1]);
}
void upd1(I i,Lli v){
  for((get<1>(segs1[i+=n])+=v)%=MOD;i>1;i>>=1)segs1[i>>1]=cmb1(segs1[i&~1],segs1[i|1]);
}
void upd2(I l,I r,Lli v){
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)(segs2[l++]+=v)%=MOD;
    if(r&1)(segs2[--r]+=v)%=MOD;
  }
}
tuple<Lli,Lli,I>qry1(I l,I r){
  tuple<Lli,Lli,I>lrs={0,0,-1},rrs={0,0,-1};
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)lrs=cmb1(lrs,segs1[l++]);
    if(r&1)rrs=cmb1(segs1[--r],rrs);
  }
  return cmb1(lrs,rrs);
}
Lli qry2(I i){
  Lli res=0;
  for(i+=n;i>0;i>>=1)(res+=segs2[i])%=MOD;
  return res;
}
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
void dfs1(I a,I p=-1){
  sizs[a]=1;
  for(auto&b:adjs[a])if(b!=p){
    dfs1(b,a);
    sizs[a]+=sizs[b];
    if(sizs[b]>sizs[adjs[a][0]])swap(b,adjs[a][0]);
  }
}
void dfs2(I a,I p=-1){
  tbgs[a]=tim++;
  asn(tbgs[a],a);
  for(auto b:adjs[a])if(b!=p){
    tops[b]=b==adjs[a][0]?tops[a]:b;
    pars[b]=a;
    dfs2(b,a);
  }
  teds[a]=tim;
}
Lli pat(I i){
  tuple<Lli,Lli,I>res={0,0,-1};
  for(;tops[i]!=tops[0];i=pars[tops[i]])res=cmb1(qry1(tbgs[tops[i]],tbgs[i]+1),res);
  return get<0>(cmb1(qry1(tbgs[0],tbgs[i]+1),res));
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>n>>q;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  dfs1(0),dfs2(0);
  bld1();
  Lli den=inv(n),tot=0;
  while(q--){
    I t;cin>>t;
    if(t==1){
      I v,d;cin>>v>>d,v--;
      (tot+=(Lli)n*d)%=MOD;
      upd1(tbgs[v],d);
      upd2(0,tbgs[v],(Lli)(n-sizs[v])*d%MOD);
      upd2(teds[v],n,(Lli)(n-sizs[v])*d%MOD);
    }
    if(t==2){
      I v;cin>>v,v--;
      Lli res=0;
      (res+=tot)%=MOD;
      (res-=pat(v)+qry2(tbgs[v]))%=MOD;
      (res*=den)%=MOD;
      printf("%lli\n",res+(res<0)*MOD);
    }
  }
}