#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I MIN=-1e8;
vector<I>adjs[N];
tuple<I,I,I>dp[N][2];
tuple<I,I,I,I>res={MIN,-1,-1,-1};
void dfs(I a,I p=-1){
  dp[a][0]={0,a,-1},dp[a][1]={MIN,-1,-1};
  pair<I,I>x={MIN,-1},y={MIN,-1},z={MIN,-1};
  for(auto b:adjs[a])if(b!=p){
    dfs(b,a);
    res=max(res,{get<0>(dp[a][0])+get<0>(dp[b][1])+1,get<1>(dp[a][0]),get<1>(dp[b][1]),get<2>(dp[b][1])});
    res=max(res,{get<0>(dp[a][1])+get<0>(dp[b][0])+1,get<1>(dp[a][1]),get<2>(dp[a][1]),get<1>(dp[b][0])});
    dp[a][0]=max(dp[a][0],{get<0>(dp[b][0])+1,get<1>(dp[b][0]),-1});
    dp[a][1]=max(dp[a][1],{get<0>(dp[b][1])+1,get<1>(dp[b][1]),get<2>(dp[b][1])});
    if(get<0>(dp[b][0])+1>get<0>(x)){
      z=y,y=x,x={get<0>(dp[b][0])+1,get<1>(dp[b][0])};
    }else if(get<0>(dp[b][0])+1>get<0>(y)){
      z=y,y={get<0>(dp[b][0])+1,get<1>(dp[b][0])};
    }else if(get<0>(dp[b][0])+1>get<0>(z)){
      z={get<0>(dp[b][0])+1,get<1>(dp[b][0])};
    }
  }
  dp[a][1]=max(dp[a][1],{get<0>(x),get<1>(x),a});
  dp[a][1]=max(dp[a][1],{get<0>(x)+get<0>(y),get<1>(x),get<1>(y)});
  res=max(res,{get<0>(x)+get<0>(y),get<1>(x),get<1>(y),a});
  res=max(res,{get<0>(x)+get<0>(y)+get<0>(z),get<1>(x),get<1>(y),get<1>(z)});
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs(0);
  auto[tot,x,y,z]=res;
  printf("%i\n",tot);
  printf("%i %i %i\n",x+1,y+1,z+1);
}