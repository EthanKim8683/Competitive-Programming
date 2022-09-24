#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;

const I N=200000;

vector<pair<I,I>>adjs[N];
vector<I>cols[N-1];
I res=0;

void dfs(I a,I p=-1,I c=-1){
  I col=0;
  for(auto[b,i]:adjs[a]){
    if(b==p)continue;
    col+=col==c;
    cols[col].push_back(i);
    res=max(res,col);
    dfs(b,a,col++);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back({v,i});
    adjs[v].push_back({u,i});
  }
  dfs(0);
  printf("%i\n",++res);
  for(I i=0;i<res;i++){
    printf("%i ",cols[i].size());
    for(auto i:cols[i])printf("%i ",i+1);
    printf("\n");
  }
  return 0;
}