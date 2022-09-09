#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;

const I N=5e4;

vector<I>adjs[N];
I ress[N];

void dfs(I a,I p=-1){
  ress[a]=p;
  for(auto b:adjs[a])
    if(b!=p)dfs(b,a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,r1,r2;cin>>n>>r1>>r2,r1--,r2--;
  for(I i=0;i<n;i++){
    if(i==r1)continue;
    I p;cin>>p,p--;
    adjs[p].push_back(i);
    adjs[i].push_back(p);
  }
  dfs(r2);
  for(I i=0;i<n;i++)
    if(ress[i]!=-1)printf("%i ",ress[i]+1);
  return 0;
}