#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;

const I N=200000;

vector<pair<I,I>>adjs[N];
I sizs[N];
I ress[N-1];
I r;

void dfs(I a,I p=-1,I c=-1){
  I i=0;
  for(auto[b,j]:adjs[a])if(b!=p){
    i+=i==c;
    dfs(b,a,ress[j]=i++%r);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n-1;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back({y,i});
    adjs[y].push_back({x,i});
  }
  for(I i=0;i<n;i++)sizs[i]=adjs[i].size();
  sort(sizs,sizs+n);
  r=sizs[n-1-k];
  dfs(0);
  printf("%i\n",r);
  for(I i=0;i<n-1;i++)printf("%i ",ress[i]+1);
}