#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I Q=1e5;
const I N=Q;
pair<C,I>qrys[Q];
vector<I>adjs[N];
map<I,pair<I,I>>rels[N];
map<I,I>recs[N];
multiset<I>vals[N];
I sizs[N];
B viss[N];
I dfs1(I a,I p=-1){
  sizs[a]=1;
  for(auto b:adjs[a])if(b!=p&&!viss[b])sizs[a]+=dfs1(b,a);
  return sizs[a];
}
I dfs2(I a,I siz,I p=-1){
  for(auto b:adjs[a])if(b!=p&&!viss[b]&&sizs[b]*2>siz)return dfs2(b,siz,a);
  return a;
}
void dfs3(I a,I r,I c,I p,I d){
  rels[a][c]={r,d};
  for(auto b:adjs[a])if(b!=p&&!viss[b])dfs3(b,r,c,a,d+1);
}
void dfs4(I a){
  a=dfs2(a,dfs1(a));
  viss[a]=1;
  rels[a][a]={a,0};
  for(auto b:adjs[a])if(!viss[b])dfs3(b,b,a,a,1);
  for(auto b:adjs[a])if(!viss[b])dfs4(b);
}
void add(I i){
  for(auto[j,val]:rels[i]){
    auto[i,d]=val;
    if(recs[j].count(i))vals[j].erase(vals[j].find(recs[j][i]));
    recs[j][i]=-max(-recs[j][i],d);
    vals[j].insert(recs[j][i]);
  }
}
I qry(I i){
  I res=0;
  for(auto[j,val]:rels[i]){
    auto[i,d]=val;
    vals[j].erase(vals[j].find(recs[j][i]));
    if(vals[j].size())res=max(res,d-*vals[j].begin());
    vals[j].insert(recs[j][i]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
#ifndef ETHANKIM8683
  freopen("newbarn.in","r",stdin);
  freopen("newbarn.out","w",stdout);
#endif
  I q;cin>>q;
  for(I i=0;i<q;i++){
    C t;I x;cin>>t>>x,x--;
    qrys[i]={t,x};
  }
  I n=0;
  for(I i=0;i<q;i++){
    auto[t,p]=qrys[i];
    if(t!='B')continue;
    if(p>=0){
      adjs[n].push_back(p);
      adjs[p].push_back(n);
    }
    n++;
  }
  for(I i=0;i<n;i++)if(!viss[i])dfs4(i);
  I j=0;
  for(I i=0;i<q;i++){
    auto[t,x]=qrys[i];
    if(t=='B')add(j++);
    if(t=='Q')printf("%i\n",qry(x));
  }
}