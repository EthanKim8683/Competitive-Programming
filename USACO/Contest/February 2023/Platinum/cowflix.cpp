#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
using Lli=long long int;
const I N=2e5;
C s_arr[N];
vector<I>adjs[N];
B viss[N];
deque<pair<Lli,Lli>>stks;
Lli slv(pair<Lli,Lli>f1,pair<Lli,Lli>f2){
  Lli n=f2.second-f1.second,d=f1.first-f2.first;
  return n/d-((n^d)<0&&n%d);
}
void upd(pair<Lli,Lli>f){
  while(stks.size()>1&&slv(stks.end()[-1],f)<=slv(stks.end()[-1],stks.end()[-2]))stks.pop_back();
  stks.push_back(f);
}
Lli qry(Lli x){
  while(stks.size()>1&&slv(stks[0],stks[1])<x)stks.pop_front();
  auto[m,b]=stks.front();
  return m*x+b;
}
pair<I,I>dfs1(I a,I p=-1){
  if(viss[a])return{0,0};
  if(s_arr[a])return{0,1};
  pair<I,I>res={1,0};
  for(auto b:adjs[a])if(b!=p){
    auto[x,y]=dfs1(b,a);
    res.first+=x,res.second+=y;
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>s_arr[i];
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  for(I i=0;i<n;i++)s_arr[i]-='0';
  for(I i=0;i<n;i++)if(!viss[i]&&!s_arr[i]){
    auto[x,y]=dfs1(i);
  }
}
/*
solve each non-watch group independently

dijkstra's for each state
*/