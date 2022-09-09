#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I N=3e5;
const Lli MAX=1e18;

vector<pair<I,I>>adjs[N];
priority_queue<pair<Lli,I>>que;
Lli diss[N];
I movs[N];
B viss[N];
I w_arr[N];
vector<I>ress;

void add(Lli d,I i,I m){
  if(d>=diss[i])return;
  que.push({-(diss[i]=d),i}),movs[i]=m;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  fill_n(diss,n,MAX);
  for(I i=0;i<m;i++){
    I x,y,w;cin>>x>>y>>w,x--,y--;
    adjs[x].push_back({y,i});
    adjs[y].push_back({x,i});
    w_arr[i]=w;
  }
  add(0,0,-1);
  I vis=0;
  while(que.size()&&vis<k+1){
    auto[d,a]=que.top();que.pop();
    if((d*=-1)!=diss[a])continue;
    viss[a]=1,vis++;
    for(auto[b,i]:adjs[a])add(d+w_arr[i],b,i);
  }
  for(I i=0;i<n;i++){
    if(!viss[i])continue;
    I m=movs[i];
    if(m!=-1)ress.push_back(m);
  }
  printf("%i\n",ress.size());
  for(auto i:ress)printf("%i ",i+1);
  return 0;
}