#include<iostream>
#include<cstdio>
#include<map>
#include<tuple>
#include<vector>
#include<deque>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I N=1e5;

vector<tuple<I,I,Lli>>ress;
map<I,Lli>bals;
deque<I>que;

B cmp(I a,I b){
  return bals[a]>bals[b];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v;Lli d;cin>>u>>v>>d;
    bals[u-1]-=d,bals[v-1]+=d;
  }
  for(I i=0;i<n;i++)if(bals[i])
    que.push_back(i);
  sort(que.begin(),que.end(),cmp);
  while(que.size()){
    I u=que.front(),v=que.back();
    Lli d=min(bals[u],-bals[v]);
    ress.push_back({v,u,d});
    if(!(bals[u]-=d))que.pop_front();
    if(!(bals[v]+=d))que.pop_back();
  }
  printf("%i\n",ress.size());
  for(auto[i,j,d]:ress)
    printf("%i %i %lli\n",i+1,j+1,d);
  return 0;
}