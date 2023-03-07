#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I LOGN=17;
const I FIXN=1<<LOGN;
vector<I>adjs[N];
tuple<I,I,I>vals[2*FIXN];
B dels[2*FIXN];
I sizs[N],pars[N],tops[N];
I tbgs[N],teds[N];
I tim=0;
tuple<I,I,I>vcb(tuple<I,I,I>a,tuple<I,I,I>b){
  auto[s1,z1,r1]=a;auto[s2,z2,r2]=b;
  I d=min(r1,z2);r1-=d,z2-=d;
  return{s1+s2,z1+z2,r1+r2};
}
tuple<I,I,I>dcb(tuple<I,I,I>a,B b){
  return b?tuple<I,I,I>{get<0>(a),get<0>(a),0}:a;
}
void pll(I i){
  for(i+=FIXN;i>1;i>>=1)vals[i>>1]=vcb(dcb(vals[i&~1],dels[i&~1]),dcb(vals[i|1],dels[i|1]));
}
void psh(I i){
  for(I j=LOGN-1;j>=0;j--){
    I k=(i+FIXN)>>j;
    vals[k]=dcb(vals[k],dels[k]);
    if(j>0)dels[k<<1]|=dels[k],dels[k<<1|1]|=dels[k];
    dels[k]=0;
  }
}
void upd(I l,I r){
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)dels[i++]=1;
    if(j&1)dels[--j]=1;
  }
  pll(l),pll(r-1);
}
tuple<I,I,I>inc(tuple<I,I,I>a){
  auto[s,z,r]=a;
  I d=min(z,1);z-=d,r+=1-d;
  return{s,z,r};
}
tuple<I,I,I>qry(I l,I r){
  psh(l),psh(r-1);
  tuple<I,I,I>lrs={0,0,0},rrs={0,0,0};
  for(l+=FIXN,r+=FIXN;l<r;l>>=1,r>>=1){
    if(l&1)lrs=vcb(lrs,dcb(vals[l],dels[l])),l++;
    if(r&1)r--,rrs=vcb(dcb(vals[r],dels[r]),rrs);
  }
  return vcb(lrs,rrs);
}
void ini(){
  for(I i=0;i<FIXN;i++)vals[i+FIXN]={1,1,0};
  for(I i=FIXN-1;i>0;i--)vals[i]=vcb(vals[i<<1],vals[i<<1|1]);
}
void dfs1(I a){
  sizs[a]=1;
  for(auto&b:adjs[a]){
    dfs1(b);
    sizs[a]+=sizs[b];
    if(sizs[b]>sizs[adjs[a][0]])swap(b,adjs[a][0]);
  }
}
void dfs2(I a){
  tbgs[a]=tim++;
  for(auto b:adjs[a]){
    pars[b]=a;
    tops[b]=b==adjs[a][0]?tops[a]:b;
    dfs2(b);
  }
  teds[a]=tim;
}
tuple<I,I,I>pat(I i){
  tuple<I,I,I>res={0,0,0};
  for(;tops[i]!=tops[0];i=pars[tops[i]])res=vcb(qry(tbgs[tops[i]],tbgs[i]+1),res);
  return vcb(qry(tbgs[0],tbgs[i]+1),res);
}
void inc(I i){
  i=tbgs[i];
  psh(i),vals[i+FIXN]=inc(vals[i+FIXN]),pll(i);
}
void clr(I i){
  upd(tbgs[i],teds[i]);
  if(i==0)return;
  I r=get<2>(pat(pars[i]));
  i=tbgs[i];
  psh(i),get<1>(vals[i+FIXN])+=r,pll(i);
}
B slv(I i){
  auto[s,z,r]=qry(tbgs[i],tbgs[i]+1);
  if(i!=0)z-=get<2>(pat(pars[i]));
  return z<=0;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=1;i<n;i++){
    I p;cin>>p,p--;
    adjs[p].push_back(i);
  }
  ini();
  dfs1(0),dfs2(0);
  while(q--){
    I t,v;cin>>t>>v,v--;
    if(t==1)inc(v);
    if(t==2)clr(v);
    if(t==3)printf("%s\n",slv(v)?"black":"white");
  }
}