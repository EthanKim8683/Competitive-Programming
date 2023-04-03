#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=50000;
const I M=100000;
const I Q=100000;
const I MIN=-1e9;
pair<I,I>edgs[M];
I d_arr[M];
I tmps[M];
vector<tuple<I,I,I>>upds;
vector<tuple<I,I,I>>qrys;
vector<tuple<I,I,I>>curs;
map<I,set<I>>adjs[N];
vector<I>excs1;
vector<I>inds;
I excs2[M];
I pars[N];
I ress[Q];
I viss[N];
I tim1=1,tim2=1;
I n,m;
B cmp(I a,I b){
  return d_arr[a]>d_arr[b];
}
I fnd(I i){
  return pars[i]<0?i:fnd(pars[i]);
}
void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
  for(auto&[c,outs]:adjs[b]){
    adjs[c].erase(b);
    if(c==a)continue;
    for(auto i:outs){
      adjs[c][a].insert(i);
      adjs[a][c].insert(i);
    }
  }
  adjs[b].clear();
}
I siz(I i){
  return-pars[fnd(i)];
}
I dfs(I a,I w){
  if(viss[a]==tim1)return 0;
  viss[a]=tim1;
  I res=siz(a);
  for(auto&[b,outs]:adjs[a])for(auto i:outs){
    if(tmps[i]<w)continue;
    res+=dfs(b,w);
  }
  return res;
}
void slv(I d){
  curs.clear();
  while(qrys.size()){
    auto[w,s,i]=qrys.back();
    if(w<=d)break;
    qrys.pop_back(),curs.push_back({i,s,w});
  }
  if(curs.empty())return;
  sort(curs.begin(),curs.end());
  for(auto i:excs1)tmps[i]=d_arr[i];
  auto it=upds.begin();
  for(auto[i,s,w]:curs){
    while(it!=upds.end()){
      auto[j,b,r]=*it;
      if(j>i)break;
      tmps[b]=r,it++;
    }
    ress[i]=dfs(fnd(s),w),tim1++;
  }
}
void bat(){
  sort(excs1.begin(),excs1.end());
  excs1.erase(unique(excs1.begin(),excs1.end()),excs1.end());
  inds.clear();
  for(I i=0;i<m;i++){
    if(excs2[i]==tim2){
      auto[u,v]=edgs[i];
      adjs[u][v].insert(i);
      adjs[v][u].insert(i);
    }else{
      inds.push_back(i);
    }
  }
  sort(qrys.begin(),qrys.end());
  sort(inds.begin(),inds.end(),cmp);
  fill_n(pars,n,-1);
  for(auto i:inds){
    auto[u,v]=edgs[i];
    slv(d_arr[i]),uni(u,v);
  }
  slv(MIN);
  for(auto i:excs1){
    auto[u,v]=edgs[i];
    adjs[fnd(u)].clear();
    adjs[fnd(v)].clear();
  }
  for(auto[i,b,r]:upds)d_arr[b]=r;
  upds.clear(),qrys.clear();
  excs1.clear();
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v,d;cin>>u>>v>>d,u--,v--;
    edgs[i]={u,v},d_arr[i]=d;
  }
  I q;cin>>q;
  I siz=max(sqrt(log2(m)*m*n/q),1.);
  for(I i=0;i<q;i++){
    I t;cin>>t;
    if(t==1){
      I b,r;cin>>b>>r,b--;
      upds.push_back({i,b,r});
      excs1.push_back(b),excs2[b]=tim2;
    }
    if(t==2){
      I s,w;cin>>s>>w,s--;
      qrys.push_back({w,s,i});
    }
    if(upds.size()>=siz)bat(),tim2++;
  }
  bat();
  for(I i=0;i<q;i++)if(ress[i])printf("%i\n",ress[i]);
}