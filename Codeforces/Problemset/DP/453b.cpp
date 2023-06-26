#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
const I P=16;
const I A=30;
const I MAX=1e9;
I prms[]{2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
I a_arr[N];
pair<I,I>dp[N+1][1<<P];
map<I,pair<I,I>>csts[A+1];
vector<I>ress;
void dfs(I i,I j,I x,I y){
  if(i==P){
    if(!csts[x].count(j))csts[x][j]={MAX,-1};
    csts[x][j]=min(csts[x][j],{abs(x-y),y});
    return;
  }
  do dfs(i+1,j,x,y),y*=prms[i],j|=1<<i;while(abs(x-y)<abs(x-1));
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*(1<<P),pair<I,I>{MAX,-1});
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=1;i<=A;i++)dfs(0,0,i,1);
  dp[0][0]={0,-1};
  for(I i=0;i<n;i++)for(I j=0;j<(1<<P);j++){
    I a=a_arr[i];
    for(auto[k,cst]:csts[a])if(!(j&k))dp[i+1][j|k]=min(dp[i+1][j|k],{dp[i][j].first+cst.first,k});
    dp[i+1][j]=min(dp[i+1][j],{dp[i][j].first+a-1,-1});
  }
  pair<I,I>res={MAX,-1};
  for(I i=0;i<(1<<P);i++)res=min(res,{dp[n][i].first,i});
  for(I i=n,j=res.second;i>0;i--){
    auto[tot,k]=dp[i][j];
    if(k==-1){ress.push_back(1);continue;}
    ress.push_back(csts[a_arr[i-1]][k].second);
    j^=k;
  }
  reverse(ress.begin(),ress.end());
  for(auto i:ress)printf("%i ",i);
}