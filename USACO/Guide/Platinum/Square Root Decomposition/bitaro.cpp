#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100000;
const I Y=100000;
const I MAX=1e9;
const I MIN=-MAX;
vector<I>adjs[N];
vector<pair<I,I>>tops[N];
priority_queue<tuple<I,I,I,I>>ques;
I c_arr[Y];
I uses[N];
B viss[N];
I bsys[N];
I diss[N];
I tims[N];
I tim=1;
I siz;
void dfs1(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto b:adjs[a])dfs1(b);
  while(ques.size())ques.pop();
  ques.push({0,a,a,MAX});
  for(auto b:adjs[a]){
    auto[dis,x]=tops[b][0];
    ques.push({dis+1,x,b,0});
  }
  while(tops[a].size()<siz&&ques.size()){
    auto[dis1,x,b,i]=ques.top();ques.pop();
    if(uses[x]!=tim)tops[a].push_back({dis1,x}),uses[x]=tim;
    if(i+1<tops[b].size()){
      auto[dis2,y]=tops[b][i+1];
      ques.push({dis2+1,y,b,i+1});
    }
  }
  tim++;
}
I dfs2(I a){
  if(tims[a]==tim)return diss[a];
  tims[a]=tim,diss[a]=bsys[a]==tim?MIN:0;
  for(auto b:adjs[a])if(dfs2(b)!=MIN)diss[a]=max(diss[a],diss[b]+1);
  return diss[a];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,q;cin>>n>>m>>q;
  for(I i=0;i<m;i++){
    I s,e;cin>>s>>e,s--,e--;
    adjs[e].push_back(s);
  }
  siz=max(sqrt(n)/2,1.);
  for(I i=n-1;i>=0;i--)dfs1(i);
  while(q--){
    I t,y;cin>>t>>y,t--;
    for(I i=0;i<y;i++){I c;cin>>c,bsys[c_arr[i]=c-1]=tim;}
    I res=MIN;
    for(auto[dis,i]:tops[t])if(bsys[i]!=tim){res=dis;break;}
    if(res==MIN&&y>=siz)res=dfs2(t);
    printf("%i\n",res==MIN?-1:res);
    tim++;
  }
}