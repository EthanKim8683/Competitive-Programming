#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using B=bool;

const I N=248;

I seqs[N];
I dp[N][N];
B viss[N][N];
I res=0;

void cmb(I& i,I j){
  i=max(i,j);
  res=max(res,i);
}

void dfs(I i,I j){
  if(viss[i][j])return;
  viss[i][j]=true;
  for(I k=i;k<j;k++){
    dfs(i,k),dfs(k+1,j);
    if(dp[i][k]==dp[k+1][j])cmb(dp[i][j],dp[i][k]+1);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>seqs[i];
  for(I i=0;i<n;i++)cmb(dp[i][i],seqs[i]);
  dfs(0,n-1);
  printf("%i\n",res);
  return 0;
}