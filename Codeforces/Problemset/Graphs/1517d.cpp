#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;

const I N=500,M=500,K=20;
const Lli MAX=1e18;

I dx[]{-1,1,0,0},dy[]{0,0,-1,1};
vector<pair<I,I>>adjs[N][M];
Lli diss[N][M][K/2+1];
I k;

Lli dfs(I i,I j,I d){
  if(d==k/2)return 0;
  if(diss[i][j][d]!=MAX)return diss[i][j][d];
  for(auto[k,c]:adjs[i][j])
    diss[i][j][d]=min(diss[i][j][d],dfs(i+dx[k],j+dy[k],d+1)+c);
  return diss[i][j][d];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m>>k;
  fill(&diss[0][0][0],&diss[0][0][0]+sizeof(diss)/sizeof(Lli),MAX);
  for(I i=0;i<n;i++)for(I j=0;j<m-1;j++){
    I a;cin>>a;
    adjs[i][j].push_back({3,a});
    adjs[i][j+1].push_back({2,a});
  }
  for(I i=0;i<n-1;i++)for(I j=0;j<m;j++){
    I a;cin>>a;
    adjs[i][j].push_back({1,a});
    adjs[i+1][j].push_back({0,a});
  }
  if(k%2){
    for(I i=0;i<n;i++){
      for(I j=0;j<m;j++)printf("-1 ");
      printf("\n");
    }
    return 0;
  }
  for(I i=0;i<n;i++){
    for(I j=0;j<m;j++)printf("%lli ",dfs(i,j,0)*2);
    printf("\n");
  }
  return 0;
}