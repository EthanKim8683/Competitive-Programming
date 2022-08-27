#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;

const I N=2000;

vector<I>que;
vector<I>adjs[N];
I dep=1;
I mdep=0;

void dfs(I a){
  mdep=max(mdep,dep);
  dep++;
  for(auto b:adjs[a])dfs(b);
  dep--;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I p;cin>>p;
    if(p==-1)que.push_back(i);
    else adjs[p-1].push_back(i);
  }
  for(auto a:que)dfs(a);
  printf("%i\n",mdep);
  return 0;
}