#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=1e5;
const I LOGN=17;
const I FIXN=1<<LOGN;
const I MIN=-1e9;
vector<I>adjs[N];
I tbgs[N],teds[N];
I sizs[N],pars[N],tops[N],deps[N];
I vals[2*FIXN],dels[2*FIXN];
I tim=0;
void pll(I i){
  for(i+=FIXN;i>1;i>>=1)vals[i>>1]=max(vals[i]+dels[i],vals[i^1]+dels[i^1]);
}
void psh(I i){
  for(I j=LOGN-1;j>0;j--){
    I k=(i+FIXN)>>j;
    vals[k]+=dels[k];
    dels[k<<1]+=dels[k],dels[k<<1|1]+=dels[k];
    dels[k]=0;
  }
}
void upd(I l,I r,I v){
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)dels[i++]+=v;
    if(j&1)dels[--j]+=v;
  }
  pll(l),pll(r-1);
}
I qry(I l,I r){
  psh(l),psh(r-1);
  I res=MIN;
  for(l+=FIXN,r+=FIXN;l<r;l>>=1,r>>=1){
    if(l&1)res=max(res,vals[l]+dels[l]),l++;
    if(r&1)r--,res=max(res,vals[r]+dels[r]);
  }
  return res;
}
void dfs1(I a,I p){
  sizs[a]=1;
  pars[a]=p;
  for(auto&b:adjs[a])if(b!=p){
    deps[b]=deps[a]+1;
    dfs1(b,a);
    sizs[a]+=sizs[b];
    if(sizs[b]>sizs[adjs[a][0]])swap(b,adjs[a][0]);
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
I pat(I a,I b){
  I res=MIN;
  while(tops[a]!=tops[b]){
    if(deps[tops[a]]<deps[tops[b]])swap(a,b);
    res=max(res,qry(tbgs[tops[a]],tbgs[a]+1));
    a=pars[tops[a]];
  }
  if(deps[a]>deps[b])swap(a,b);
  return max(res,qry(tbgs[a],tbgs[b]+1));
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  dfs1(0,0),dfs2(0);
  I q;cin>>q;
  while(q--){
    S s;cin>>s;
    if(s=="add"){
      I t,v;cin>>t>>v,t--;
      upd(tbgs[t],teds[t],v);
    }
    if(s=="max"){
      I a,b;cin>>a>>b,a--,b--;
      printf("%i\n",pat(a,b));
    }
  }
}