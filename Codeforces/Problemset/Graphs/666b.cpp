#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=3000;
const I MAX=1e9;

vector<I>adjs[N];
queue<I>que1;
priority_queue<tuple<I,I,I,I,I>>que2;
I diss[N][N];
vector<I>inds1[N],inds2[N];
I n;
I x;
I r=0;

void add1(I d,I j){
  if(d>=diss[x][j])return;
  diss[x][j]=d,que1.push(j);
}

void add2(I i,I j,I k,I l){
  if(i>=inds2[j].size()||l>=inds1[k].size())return;
  I x=inds2[j][i],y=inds1[k][l];
  I res=diss[x][j]+diss[j][k]+diss[k][y];
  if(res>r)que2.push({res,i,j,k,l});
}

B cmp1(I a,I b){
  return diss[x][a]>diss[x][b];
}

B cmp2(I a,I b){
  return diss[a][x]>diss[b][x];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&diss[0][0],&diss[0][0]+N*N,MAX);
  I m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
  }
  for(I i=0;i<n;i++){
    x=i,add1(0,i);
    while(que1.size()){
      I a=que1.front();que1.pop();
      for(auto b:adjs[a])add1(diss[i][a]+1,b);
    }
  }
  for(I i=0;i<n;i++){
    x=i;
    for(I j=0;j<n;j++){
      if(i==j||diss[i][j]==MAX)continue;
      inds1[i].push_back(j);
    }
    for(I j=0;j<n;j++){
      if(i==j||diss[j][i]==MAX)continue;
      inds2[i].push_back(j);
    }
    sort(inds1[i].begin(),inds1[i].end(),cmp1);
    sort(inds2[i].begin(),inds2[i].end(),cmp2);
  }
  I s,t,u,v;
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)if(i!=j){
    if(diss[i][j]==MAX)continue;
    while(que2.size())que2.pop();
    add2(0,i,j,0);
    while(que2.size()){
      auto[d,x,y,z,w]=que2.top();que2.pop();
      I k=inds2[y][x],l=inds1[z][w];
      if(k!=y&&k!=z&&k!=l&&y!=z&&y!=l&&z!=l){
        r=d,s=k,t=y,u=z,v=l;
        break;
      }
      add2(x+1,y,z,w);
      add2(x,y,z,w+1);
    }
  }
  printf("%i %i %i %i\n",s+1,t+1,u+1,v+1);
}