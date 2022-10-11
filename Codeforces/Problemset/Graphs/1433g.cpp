#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1000;
const I M=1000;
const I K=1000;
const Lli MAX=1e18;

vector<pair<I,I>>adjs[N];
I w_arr[M];
pair<I,I>pats[K];
Lli diss1[N][N],diss2[N][M];
priority_queue<pair<Lli,I>>que;

void add(I d,I a,I i){
  if(d>=diss1[i][a])return;
  que.push({-(diss1[i][a]=d),a});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&diss1[0][0],&diss1[0][0]+N*N,MAX);
  fill(&diss2[0][0],&diss2[0][0]+N*M,MAX);
  I n,m,k;cin>>n>>m>>k;
  for(I i=0;i<m;i++){
    I x,y,w;cin>>x>>y>>w,x--,y--;
    adjs[x].push_back({y,i});
    adjs[y].push_back({x,i});
    w_arr[i]=w;
  }
  for(I i=0;i<k;i++){
    I a,b;cin>>a>>b,a--,b--;
    pats[i]={a,b};
  }
  for(I i=0;i<n;i++){
    add(0,i,i);
    while(que.size()){
      auto[d,a]=que.top();que.pop();
      if((d=-d)!=diss1[i][a])continue;
      for(auto[b,j]:adjs[a]){
        add(d+w_arr[j],b,i);
        diss2[i][j]=min(diss2[i][j],d);
      }
    }
  }
  Lli res=MAX;
  for(I i=0;i<m;i++){
    Lli tot=0;
    for(I j=0;j<k;j++){
      auto[a,b]=pats[j];
      tot+=min(diss1[a][b],diss2[a][i]+diss2[b][i]);
    }
    res=min(res,tot);
  }
  printf("%lli\n",res);
}