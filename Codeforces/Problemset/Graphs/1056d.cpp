#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;

const I N=1e5;

vector<I>adjs[N];
I lefs[N];

I dfs(I a){
  lefs[a]=adjs[a].size()==0;
  for(auto b:adjs[a])lefs[a]+=dfs(b);
  return lefs[a];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=1;i<n;i++){I p;cin>>p,adjs[p-1].push_back(i);}
  dfs(0);
  sort(lefs,lefs+n);
  for(I i=0;i<n;i++)printf("%i ",lefs[i]);
  return 0;
}