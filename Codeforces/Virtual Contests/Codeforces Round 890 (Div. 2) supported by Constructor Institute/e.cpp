#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=5000;
I p_arr[N];
vector<I>adjs[N];
I sizs[N];
B dp[N+1][N+1];
Lli res=0;
void dfs(I a,I p=-1){
  sizs[a]=1;
  for(auto b:adjs[a])if(b!=p){
    dfs(b,a);
    sizs[a]+=sizs[b];
  }
  I tot=sizs[a]-1,i=0;
  for(auto b:adjs[a])if(b!=p){
    for(I j=0;j<=tot;j++)dp[i][j]=0;
    i++;
  }
  for(I j=0;j<=tot;j++)dp[i][j]=0;
  dp[0][0]=1;
  i=0;
  for(auto b:adjs[a])if(b!=p){
    for(I j=tot;j>=0;j--){
      if(j+sizs[b]<=tot)dp[i+1][j+sizs[b]]|=dp[i][j];
      dp[i+1][j]|=dp[i][j];
    }
    i++;
  }
  Lli cur=0;
  for(I j=0;j<=tot;j++)if(dp[i][j])cur=max(cur,(Lli)j*(tot-j));
  res+=cur;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=1;i<n;i++){
    I p;cin>>p,p--;
    adjs[p].push_back(i);
  }
  res=0,dfs(0);
  printf("%lli\n",res);
}