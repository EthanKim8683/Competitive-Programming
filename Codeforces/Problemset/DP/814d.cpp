#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
using Lf=long double;
const I N=1000;
const Lli MIN=-1e18;
const Lf PI=3.1415926535L;
tuple<I,I,I>dans[N];
vector<I>adjs[N];
B inds[N];
Lli dp[N][3][3];
void dfs(I a){
  auto[r,x,y]=dans[a];
  Lli are=(Lli)r*r;
  if(!adjs[a].size()){
    dp[a][0][2]=are;
    dp[a][1][2]=-are;
    dp[a][2][0]=are;
    dp[a][2][1]=-are;
    return;
  }
  Lli res000_=are,res00_0=are;
  Lli res010_=-are,res01_1=are;
  Lli res101_=are,res10_0=-are;
  Lli res111_=-are,res11_1=-are;
  Lli res0212=are;
  Lli res2021=are;
  Lli res1202=-are;
  Lli res2120=-are;
  for(auto b:adjs[a]){
    dfs(b);
    res000_+=max(dp[b][0][1],dp[b][0][2]),res00_0+=max(dp[b][1][0],dp[b][2][0]);
    res010_+=max(dp[b][0][1],dp[b][0][2]),res01_1+=max(dp[b][1][1],dp[b][2][1]);
    res101_+=max(dp[b][1][1],dp[b][1][2]),res10_0+=max(dp[b][1][0],dp[b][2][0]);
    res111_+=max(dp[b][1][1],dp[b][1][2]),res11_1+=max(dp[b][1][1],dp[b][2][1]);
    res0212+=dp[b][1][2];
    res2021+=dp[b][2][1];
    res1202+=dp[b][0][2];
    res2120+=dp[b][2][0];
  }
  dp[a][0][0]=max(res000_,res00_0);
  dp[a][0][1]=max(res010_,res01_1);
  dp[a][1][0]=max(res101_,res10_0);
  dp[a][1][1]=max(res111_,res11_1);
  dp[a][0][2]=res0212;
  dp[a][2][0]=res2021;
  dp[a][1][2]=res1202;
  dp[a][2][1]=res2120;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+N*3*3,MIN);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y,r;cin>>x>>y>>r;
    dans[i]={r,x,y};
  }
  sort(dans,dans+n);
  for(I i=0;i<n;i++)for(I j=i+1;j<n;j++){
    auto[r1,x1,y1]=dans[i];auto[r2,x2,y2]=dans[j];
    I dx=x1-x2,dy=y1-y2;
    if((Lli)dx*dx+(Lli)dy*dy>(Lli)r2*r2)continue;
    adjs[j].push_back(i),inds[i]=1;
    break;
  }
  Lli res=0;
  for(I i=0;i<n;i++)if(!inds[i]){
    dfs(i);
    Lli cur=MIN;
    cur=max(cur,dp[i][0][0]);
    cur=max(cur,dp[i][0][2]);
    cur=max(cur,dp[i][2][0]);
    res+=cur;
  }
  printf("%.10Lf\n",res*PI);
}