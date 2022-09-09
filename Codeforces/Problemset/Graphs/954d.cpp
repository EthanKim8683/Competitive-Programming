#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<set>

using namespace std;

using I=int;

const I N=1000;
const I MAX=1e9;

vector<I>adjs[N];
queue<I>que[2];
I diss[N][2];
set<pair<I,I>>viss;

void add(I i,I j,I d){
  if(d>=diss[i][j])return;
  diss[i][j]=d;
  que[j].push(i);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,s,t;cin>>n>>m>>s>>t,s--,t--;
  fill(&diss[0][0],&diss[0][0]+sizeof(diss)/sizeof(I),MAX);
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
    viss.insert({min(u,v),max(u,v)});
  }
  add(s,0,0),add(t,1,0);
  for(I i=0;i<2;i++){
    while(que[i].size()){
      I a=que[i].front();que[i].pop();
      for(auto b:adjs[a])add(b,i,diss[a][i]+1);
    }
  }
  I dis=diss[t][0];
  I cnt=0;
  for(I i=0;i<n;i++)for(I j=i+1;j<n;j++){
    if(viss.find({i,j})!=viss.end())continue;
    I sds=min(diss[i][0],diss[j][0]);
    I tds=min(diss[i][1],diss[j][1]);
    cnt+=sds+tds+1>=dis;
  }
  printf("%i\n",cnt);
  return 0;
}