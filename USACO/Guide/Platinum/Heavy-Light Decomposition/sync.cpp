#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100000;
const I MIN=-1e9;
const I LOGN=17;
vector<I>adjs[N];
pair<I,I>edgs[N-1];
I sizs[N],tops[N],inds[N],invs[N];
I segs1[2*N],segs2[2*N];
I ancs[N][LOGN];
map<I,I>adds[N];
I n;
I ind=0;
void upd(I l,I r,I x){
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)segs1[l++]+=x;
    if(r&1)segs1[--r]+=x;
  }
}
void upd(I i,I x){
  for(segs2[i+=n]=x;i>1;i>>=1)segs2[i>>1]=max(segs2[i],segs2[i^1]);
}
I qry(I i){
  I res=0;
  for(i+=n;i>0;i>>=1)res+=segs1[i];
  return res;
}
I qry(I l,I r){
  I res=MIN;
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)res=max(res,segs2[l++]);
    if(r&1)res=max(res,segs2[--r]);
  }
  return res;
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
  invs[inds[a]=ind++]=a;
  upd(inds[a],inds[a]);
  for(auto b:adjs[a])if(b!=p){
    tops[b]=b==adjs[a][0]?tops[a]:b;
    dfs2(b,a);
  }
}
I par(I a){
  I res=MIN;
  for(;tops[a]!=tops[0];a=ancs[tops[a]][0])res=max(res,qry(inds[tops[a]],inds[a]+1));
  return invs[max(res,qry(inds[0],inds[a]+1))];
}
I siz(I a){
  return qry(inds[par(a)]);
}
void add(I i,I x){
  I j=par(i);
  for(;tops[i]!=tops[j];i=ancs[tops[i]][0])upd(inds[tops[i]],inds[i]+1,x);
  upd(inds[j],inds[i]+1,x);
}
void alt(I a,I b){
  if(a==ancs[b][0])swap(a,b);
  I c=par(a);
  if(c==a){
    I low=siz(a);
    upd(inds[a],MIN);
    add(b,low);
    add(a,-adds[a][b]),add(b,-adds[b][a]);
    adds[a][b]=0,adds[b][a]=0;
  }else{
    upd(inds[a],inds[a]);
    I low=siz(a);
    add(b,-low);
    I upp=siz(b);
    adds[a][b]=upp,adds[b][a]=low;
    add(a,adds[a][b]),add(b,adds[b][a]);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m,q;cin>>n>>m>>q;
  for(I i=0;i<n-1;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
    edgs[i]={x,y};
  }
  dfs1(0,0),dfs2(0);
  upd(0,n,1);
  for(I i=0;i<m;i++){
    I d;cin>>d,d--;
    auto[x,y]=edgs[d];
    alt(x,y);
  }
  while(q--){
    I c;cin>>c,c--;
    printf("%i\n",siz(c));
  }
}