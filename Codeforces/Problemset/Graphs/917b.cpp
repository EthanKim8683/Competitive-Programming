#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using C=char;

const I N=100;

vector<pair<I,I>>adjs[N];
I ress[N][N][26][2];

I dfs(I a,I b,I c,I p){
  if(ress[a][b][c][p]!=-1)return ress[a][b][c][p];
  for(auto[d,e]:adjs[a])if(e>=c)
    if(dfs(b,d,e,!p)==p)return ress[a][b][c][p]=p;
  return ress[a][b][c][p]=!p;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill(&ress[0][0][0][0],&ress[0][0][0][0]+sizeof(ress)/sizeof(I),-1);
  for(I i=0;i<m;i++){
    I v,u;C c;cin>>v>>u>>c;
    adjs[v-1].push_back({u-1,c-'a'});
  }
  for(I i=0;i<n;i++){
    for(I j=0;j<n;j++)printf("%c",dfs(i,j,0,1)?'A':'B');
    printf("\n");
  }
  return 0;
}