#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3000;
const Lli MAX=1e18;
Lli a_arr[N];
Lli dp[N][N];
vector<Lli>cpss;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*N,MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)a_arr[i]-=i;
  for(I i=0;i<n;i++)cpss.push_back(a_arr[i]);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<cpss.size();i++)dp[0][i]=abs(cpss[i]-a_arr[0]);
  for(I i=1;i<n;i++){
    for(I j=0;j+1<cpss.size();j++)dp[i-1][j+1]=min(dp[i-1][j+1],dp[i-1][j]);
    for(I j=0;j<cpss.size();j++)dp[i][j]=dp[i-1][j]+abs(cpss[j]-a_arr[i]);
  }
  printf("%lli\n",*min_element(dp[n-1],dp[n-1]+cpss.size()));
}
/*
if we subtract i from each a[i], simply finding the cheapest non-decreasing
sequence can be done easily using dynamic programming path on grids
*/