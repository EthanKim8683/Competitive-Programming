#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;

const I N=2e5;

vector<I>adjs[N];
I cols[N];
I res=0;

void dfs(I a,I p=-1){
  I c1=cols[a],c2=p==-1?-1:cols[p];
  I i=0;
  for(auto b:adjs[a]){
    if(b==p)continue;
    while(i==c1||i==c2)i++;
    res=max(res,cols[b]=i++);
    dfs(b,a);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  dfs(0);
  printf("%i\n",res+1);
  for(I i=0;i<n;i++)printf("%i ",cols[i]+1);
  return 0;
}