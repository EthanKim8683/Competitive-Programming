#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=3e5;
const I Q=6e5;
const Lli MAX=1e18;
const I LOGN=19;
Lli w_arr[N];
vector<pair<I,I>>adjs[N];
pair<Lli,Lli>wgts[N-1];
pair<I,I>edgs[N-1];
pair<I,I>qrys[Q];
vector<I>inds[N];
I acts[Q];
Lli ress[Q];
I sizs[N];
B viss[N];
Lli diss[2*N][2];
priority_queue<tuple<Lli,I,I>>ques;
I tim=0;
void add1(I i,Lli d){
  if(d<w_arr[i])w_arr[i]=d,ques.push({-d,1,i});
}
void add2(I i,Lli d){
  I i1=i/2,i2=i%2;
  auto[w1,w2]=wgts[i1];
  if(i2==0&&d<w1)wgts[i1]={d,w2},ques.push({-d,0,i});
  if(i2==1&&d<w2)wgts[i1]={w1,d},ques.push({-d,0,i});
}
I dfs1(I a,I p=-1){
  sizs[a]=1;
  for(auto[b,i]:adjs[a])if(b!=p&&!viss[b])sizs[a]+=dfs1(b,a);
  return sizs[a];
}
I dfs2(I a,I siz,I p=-1){
  for(auto[b,i]:adjs[a])if(b!=p&&!viss[b]&&sizs[b]*2>siz)return dfs2(b,siz,a);
  return a;
}
void dfs4(I a,I p=-1,Lli d1=0,Lli d2=0,Lli d3=MAX,Lli d4=MAX){
  d1=min(d1,d4+w_arr[a]),d4=min(d4,d1+w_arr[a]);
  d3=min(d3,d2+w_arr[a]),d2=min(d2,d3+w_arr[a]);
  diss[a*2][0]=d1,diss[a*2+1][0]=d4;
  diss[a*2][1]=d3,diss[a*2+1][1]=d2;
  for(auto i:inds[a]){
    if(acts[i]==tim){
      auto[x,y]=qrys[i];
      ress[i]=min(ress[i],diss[x][0]+diss[y][0]);
      ress[i]=min(ress[i],diss[x][1]+diss[y][1]);
      continue;
    }
    acts[i]=tim;
  }
  for(auto[b,i]:adjs[a])if(b!=p&&!viss[b]){
    auto[w1,w2]=wgts[i];
    dfs4(b,a,d1+w1,d2+w2,d3+w1,d4+w2);
  }
}
void dfs3(I a){
  a=dfs2(a,dfs1(a));
  viss[a]=1;
  tim++;
  dfs4(a);
  for(auto[b,i]:adjs[a])if(!viss[b])dfs3(b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>w_arr[i];
  for(I i=0;i<n-1;i++){
    I x,y;Lli w1,w2;cin>>x>>y>>w1>>w2,x--,y--;
    adjs[x].push_back({y,i});
    adjs[y].push_back({x,i});
    wgts[i]={w1,w2};
    edgs[i]={x,y};
  }
  for(I i=0;i<n-1;i++){
    auto[w1,w2]=wgts[i];
    ques.push({-w1,0,i*2+0});
    ques.push({-w2,0,i*2+1});
  }
  for(I i=0;i<n;i++)ques.push({-w_arr[i],1,i});
  while(ques.size()){
    auto[w,t,i]=ques.top();ques.pop(),w=-w;
    if(t==0){
      I i1=i/2,i2=i%2;
      auto[w1,w2]=wgts[i1];
      auto[j,k]=edgs[i1];
      if(i2==0){
        if(w!=w1)continue;
        add1(j,w_arr[k]+w1+w2);
        add1(k,w_arr[j]+w1+w2);
      }
      if(i2==1){
        if(w!=w2)continue;
        add1(j,w_arr[k]+w1+w2);
        add1(k,w_arr[j]+w1+w2);
      }
    }
    if(t==1){
      if(w!=w_arr[i])continue;
      for(auto[j,k]:adjs[i]){
        auto[w1,w2]=wgts[k];
        add2(k*2+0,w2+w_arr[i]+w_arr[j]);
        add2(k*2+1,w1+w_arr[i]+w_arr[j]);
        add1(j,w_arr[i]+w1+w2);
      }
    }
  }
  I q;cin>>q;
  for(I i=0;i<q;i++){
    I u,v;cin>>u>>v,u--,v--;
    qrys[i]={u,v};
    inds[u/2].push_back(i);
    inds[v/2].push_back(i);
  }
  fill_n(ress,q,MAX);
  dfs3(0);
  for(I i=0;i<q;i++)printf("%lli\n",ress[i]);
}