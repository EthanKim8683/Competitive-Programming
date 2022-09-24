#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<tuple>

using namespace std;

using I=int;

const I N=1e5;
const I M=1e5;
const I MAX=1e9;

vector<pair<I,I>>adjs[N];
tuple<I,I,I>edgs[M];
priority_queue<pair<I,I>>que;
I diss[N];

void add(I d,I i){
  if(d>=diss[i])return;
  que.push({-(diss[i]=d),i});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,s;cin>>n>>m>>s,s--;
  fill_n(diss,n,MAX);
  for(I i=0;i<m;i++){
    I v,u,w;cin>>v>>u>>w,v--,u--;
    adjs[v].push_back({u,w});
    adjs[u].push_back({v,w});
    edgs[i]={v,u,w};
  }
  I l;cin>>l;
  add(0,s);
  while(que.size()){
    auto[d,a]=que.top();que.pop();
    if((d*=-1)!=diss[a])continue;
    for(auto[b,w]:adjs[a])add(d+w,b);
  }
  I res=0;
  for(I i=0;i<n;i++)res+=diss[i]==l;
  for(I i=0;i<m;i++){
    auto[a,b,w]=edgs[i];
    I dis1=diss[a],dis2=diss[b];
    I far=dis1+dis2+w;
    if(far>l*2)res+=dis1<l,res+=dis2<l;
    if(far==l*2)res+=dis1<l&&dis2<l;
  }
  printf("%i\n",res);
  return 0;
}