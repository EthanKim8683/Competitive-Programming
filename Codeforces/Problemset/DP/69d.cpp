#include<bits/stdc++.h>
using namespace std;
using I=int;
const I X=200;
const I Y=200;
const I N=200;
pair<I,I>vecs[N];
I dp[2*X+1][2*Y+1][2][2][2];
I n,d;
I dfs(I x1,I y1,I skp1,I skp2,I mov){
  if(x1*x1+y1*y1>d*d)return mov;
  if(dp[x1+X][y1+Y][skp1][skp2][mov]!=-1)return dp[x1+X][y1+Y][skp1][skp2][mov];
  if(mov==0&&!skp1&&dfs(y1,x1,1,skp2,!mov)==mov)return dp[x1+X][y1+Y][skp1][skp2][mov]=mov;
  if(mov==1&&!skp2&&dfs(y1,x1,skp1,1,!mov)==mov)return dp[x1+X][y1+Y][skp1][skp2][mov]=mov;
  for(I i=0;i<n;i++){
    auto[x2,y2]=vecs[i];
    if(dfs(x1+x2,y1+y2,skp1,skp2,!mov)==mov)return dp[x1+X][y1+Y][skp1][skp2][mov]=mov;
  }
  return dp[x1+X][y1+Y][skp1][skp2][mov]=!mov;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0][0][0],&dp[0][0][0][0][0]+(2*X+1)*(2*Y+1)*2*2*2,-1);
  I x,y;cin>>x>>y>>n>>d;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    vecs[i]={x,y};
  }
  printf("%s\n",dfs(x,y,0,0,0)==0?"Anton":"Dasha");
}