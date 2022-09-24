#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#include<tuple>

using namespace std;

using I=int;

const I N=3000;
const I MAX=1e9;

vector<I>adjs[N];
I diss[N][N];
I pars[N][N];
queue<pair<I,I>>que;
set<tuple<I,I,I>>invs;
vector<I>ress;

void add(I d,I i,I j,I k){
  if(invs.count({i,j,k}))return;
  if(d>=diss[j][k])return;
  que.push({j,k}),diss[j][k]=d,pars[j][k]=i;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  fill(&diss[0][0],&diss[0][0]+sizeof(diss)/sizeof(I),MAX);
  for(I i=0;i<m;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  for(I i=0;i<k;i++){
    I a,b,c;cin>>a>>b>>c;
    invs.insert({a-1,b-1,c-1});
  }
  for(auto i:adjs[0])add(1,-1,0,i);
  while(que.size()){
    auto[i,j]=que.front();que.pop();
    I d=diss[i][j];
    if(j==n-1){
      ress.push_back(j);
      ress.push_back(i);
      for(I l=0;l<d-1;l++){
        I k=pars[i][j];
        ress.push_back(k);
        j=i,i=k;
      }
      reverse(ress.begin(),ress.end());
      printf("%i\n",d);
      for(auto i:ress)printf("%i ",i+1);
      exit(0);
    }
    for(auto k:adjs[j])add(d+1,i,j,k);
  }
  printf("-1\n");
}