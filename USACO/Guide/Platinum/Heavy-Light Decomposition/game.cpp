#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=50000;
const I LOGN=16;
const I FIXN=1<<LOGN;
I a_arr[N];
vector<I>adjs[N];
pair<I,I>vals[2*FIXN];
I dels[2*FIXN];
map<I,Lli>ixcs[N];
Lli excs[N];
I sizs[N],tops[N],pars[N];
I tbgs[N],teds[N];
I tim=0;
pair<I,I>vcb(pair<I,I>a,pair<I,I>b){
  return{a.first+b.first,a.second+b.second};
}
pair<I,I>dcb(pair<I,I>a,I b){
  if(b%2)swap(a.first,a.second);
  return a;
}
void pll(I i){
  for(i+=FIXN;i>1;i>>=1)vals[i>>1]=vcb(dcb(vals[i],dels[i]),dcb(vals[i^1],dels[i^1]));
}
void psh(I i){
  for(I j=LOGN-1;j>=0;j--){
    I k=(i+FIXN)>>j;
    vals[k]=dcb(vals[k],dels[k]);
    if(j)dels[k<<1]+=dels[k],dels[k<<1|1]+=dels[k];
    dels[k]=0;
  }
}
void asn(I i,I x){
  vals[i+FIXN]={x,1-x};
}
void bld(){
  for(I i=FIXN-1;i>0;i--)vals[i]=vcb(vals[i<<1],vals[i<<1|1]);
}
void upd(I l,I r){
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)dels[i++]++;
    if(j&1)dels[--j]++;
  }
  pll(l),pll(r-1);
}
pair<I,I>qry(I l,I r){
  psh(l),psh(r-1);
  pair<I,I>res={0,0};
  for(l+=FIXN,r+=FIXN;l<r;l>>=1,r>>=1){
    if(l&1)res=vcb(res,dcb(vals[l],dels[l])),l++;
    if(r&1)r--,res=vcb(res,dcb(vals[r],dels[r]));
  }
  return res;
}
void dfs1(I a,I p=-1){
  sizs[a]=1;
  pars[a]=p;
  for(auto&b:adjs[a])if(b!=p){
    dfs1(b,a);
    sizs[a]+=sizs[b];
    if(adjs[a][0]==p||sizs[b]>sizs[adjs[a][0]])swap(b,adjs[a][0]);
  }
}
void dfs2(I a,I p=-1){
  tbgs[a]=tim++;
  for(auto b:adjs[a])if(b!=p){
    tops[b]=b==adjs[a][0]?tops[a]:b;
    dfs2(b,a);
  }
  teds[a]=tim;
}
void rep(I i,I j,Lli v){
  excs[i]-=ixcs[i][j],excs[i]+=ixcs[i][j]=v*v;
}
void trv(I i){
  for(;tops[i]!=tops[0];i=pars[tops[i]]){
    I j=tops[i];
    upd(tbgs[j],tbgs[i]+1);
    rep(pars[j],j,qry(tbgs[j],teds[j]).first);
  }
  upd(tbgs[0],tbgs[i]+1);
}
Lli slv(I i){
  Lli rot=qry(tbgs[i],tbgs[i]+1).first,sum=qry(tbgs[i],teds[i]).first,hea=0;
  if(adjs[i].size()){
    I j=adjs[i][0];
    if(j!=pars[i])hea=qry(tbgs[j],teds[j]).first;
  }
  return(sum*sum-excs[i]-hea*hea-rot*rot)/2;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  dfs1(0),dfs2(0);
  for(I i=0;i<n;i++)asn(tbgs[i],a_arr[i]);
  bld();
  for(I i=1;i<n;i++)if(tops[i]==i)rep(pars[i],i,qry(tbgs[i],teds[i]).first);
  while(q--){
    I o,x;cin>>o>>x,x--;
    if(o==1)trv(x);
    if(o==2)printf("%lli\n",slv(x));
  }
}