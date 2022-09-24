#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<vector>
#include<tuple>
#include<queue>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=3e5;
const I M=3e5;
const Lli MAX=1e18;

tuple<I,I,I>edgs[M];
vector<pair<I,I>>adjs1[N];
I adjs2[N];
Lli diss[N];
priority_queue<pair<Lli,I>>que;
vector<I>ress;

void add(Lli d,I i,I j){
  if(d>diss[i])return;
  if(d==diss[i]&&get<0>(edgs[j])<get<0>(edgs[adjs2[i]]))adjs2[i]=j;
  if(d<diss[i])que.push({-(diss[i]=d),i}),adjs2[i]=j;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(diss,n,MAX);
  for(I i=0;i<m;i++){
    I u,v,w;cin>>u>>v>>w,u--,v--;
    adjs1[u].push_back({v,i});
    adjs1[v].push_back({u,i});
    edgs[i]={w,u,v};
  }
  I u;cin>>u,u--;
  add(0,u,-1);
  while(que.size()){
    auto[d,a]=que.top();que.pop();
    if((d=-d)!=diss[a])continue;
    for(auto[b,i]:adjs1[a])add(d+get<0>(edgs[i]),b,i);
  }
  Lli res=0;
  for(I i=0;i<n;i++)if(i!=u){
    I j=adjs2[i];
    res+=get<0>(edgs[j]),ress.push_back(j);
  }
  printf("%lli\n",res);
  for(auto i:ress)printf("%i ",i+1);
  return 0;
}