#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=100;

pair<I,I>rngs[N];
B viss[N];
I c=0;

void dfs(I a){
  if(viss[a])return;
  viss[a]=true;
  for(I i=0;i<=c;i++){
    if(a==i)continue;
    auto[x,y]=rngs[a];
    auto[z,w]=rngs[i];
    if(z<x&&x<w||z<y&&y<w)dfs(i);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  while(n--){
    I t;cin>>t;
    if(t==1){
      I x,y;cin>>x>>y;
      rngs[c++]={x,y};
    }
    if(t==2){
      I a,b;cin>>a>>b;
      fill_n(viss,c,false);
      dfs(a-1);
      if(viss[b-1])printf("YES\n");
      else printf("NO\n");
    }
  }
  return 0;
}