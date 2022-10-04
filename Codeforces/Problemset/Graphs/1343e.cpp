#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;
const I M=2e5;
const Lli MAX=1e18;

I p_arr[M];
Lli ps[M+1];
vector<I>adjs[N];
Lli diss[3][N];
queue<I>que;
I n;

void add(I d,I a,I i){
  if(d>=diss[i][a])return;
  diss[i][a]=d,que.push(a);
}

void bfs(I a,I i){
  fill_n(diss[i],n,MAX);
  add(0,a,i);
  while(que.size()){
    I a=que.front();que.pop();
    for(auto b:adjs[a])add(diss[i][a]+1,b,i);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I m,a,b,c;cin>>n>>m>>a>>b>>c,a--,b--,c--;
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<m;i++)cin>>p_arr[i];
    for(I i=0;i<m;i++){
      I v,u;cin>>v>>u,v--,u--;
      adjs[v].push_back(u);
      adjs[u].push_back(v);
    }
    sort(p_arr,p_arr+m);
    for(I i=0;i<m;i++)ps[i+1]=p_arr[i];
    for(I i=0;i<m;i++)ps[i+1]+=ps[i];
    bfs(a,0),bfs(b,1),bfs(c,2);
    Lli res=MAX;
    for(I i=0;i<n;i++){
      I dis0=diss[0][i],dis1=diss[1][i],dis2=diss[2][i];
      if(dis0+dis1+dis2>m)continue;
      res=min(res,2*ps[dis1]+ps[dis0+dis1+dis2]-ps[dis1]);
    }
    printf("%lli\n",res);
  }
}