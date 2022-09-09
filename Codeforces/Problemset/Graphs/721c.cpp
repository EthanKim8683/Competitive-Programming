#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<tuple>

using namespace std;

using I=int;

const I N=5000;
const I MAX=2e9;

vector<pair<I,I>>adjs[N];
I diss[N][N+1];
I pars[N][N+1];
priority_queue<tuple<I,I,I>>que;
vector<I>ress;
I n,t;
I ccur=0,icur;

void add(I i,I c,I d,I p){
  if(d>t||d>=diss[i][c])return;
  pars[i][c]=p;
  que.push({-(diss[i][c]=d),i,c});
  if(i==n-1&&c>ccur)ccur=c,icur=i;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m>>t;
  fill(&diss[0][0],&diss[0][0]+sizeof(diss)/sizeof(I),MAX);
  for(I i=0;i<m;i++){
    I u,v,t;cin>>u>>v>>t,u--,v--;
    adjs[u].push_back({v,t});
  }
  add(0,1,0,-1);
  while(que.size()){
    auto[d,a,c]=que.top();que.pop();
    if((d*=-1)!=diss[a][c])continue;
    for(auto[b,t]:adjs[a])add(b,c+1,d+t,a);
  }
  printf("%i\n",ccur);
  while(ccur){
    ress.push_back(icur);
    icur=pars[icur][ccur],ccur-=1;
  }
  reverse(ress.begin(),ress.end());
  for(auto i:ress)printf("%i ",i+1);
  return 0;
}