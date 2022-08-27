#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;

const I K=26;

vector<I>adjs[K];
vector<I>euls;

void dfs(I a){
  while(adjs[a].size()){
    I b=adjs[a].back();adjs[a].pop_back();
    dfs(b);
  }
  euls.push_back(a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<k;i++)for(I j=0;j<k;j++)
    adjs[i].push_back(j);
  dfs(0);
  printf("%c",euls[0]+'a');
  for(I i=0;i<n-1;i++)printf("%c",euls[1+i%(k*k)]+'a');
  return 0;
}