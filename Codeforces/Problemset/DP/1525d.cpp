#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=5000;
const I MAX=1e9;

I a_arr[N];
I dp[N+1][N+1];
vector<I>inds0;
vector<I>inds1;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*(N+1),MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(a==1)inds1.push_back(i);
    if(a==0)inds0.push_back(i);
  }
  I x=inds1.size(),y=inds0.size();
  dp[0][0]=0;
  for(I i=0;i<x;i++)for(I j=0;j<y;j++){
    dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]+abs(inds1[i]-inds0[j]));
    dp[i][j+1]=min(dp[i][j+1],dp[i][j]);
  }
  printf("%i\n",*min_element(dp[x],dp[x]+y+1));
}