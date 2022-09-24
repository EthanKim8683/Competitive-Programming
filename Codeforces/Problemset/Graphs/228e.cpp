#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=100;

vector<pair<I,I>>adjs[N];
vector<I>ress;
B viss[N];
I cols[N];

B dfs(I a,I col){
  if(viss[a])return cols[a]==col;
  viss[a]=1;
  cols[a]=col;
  if(col)ress.push_back(a);
  for(auto[b,c]:adjs[a])
    if(!dfs(b,c^col==0))return 0;
  return 1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b,c;cin>>a>>b>>c,a--,b--;
    adjs[a].push_back({b,c});
    adjs[b].push_back({a,c});
  }
  for(I i=0;i<n;i++)if(!dfs(i,cols[i]))
    printf("Impossible\n"),exit(0);
  printf("%i\n",ress.size());
  for(auto i:ress)printf("%i ",i+1);
}