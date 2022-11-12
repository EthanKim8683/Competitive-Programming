#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1000;
const I K=2000;
const Lli MAX=1e18;

Lli a_arr[N];
Lli b_arr[K];
Lli dp[N+1][K+1];

void cmb(Lli&a,Lli b){
  a=min(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*(K+1),MAX);
  I n,k;Lli p;cin>>n>>k>>p;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<k;i++)cin>>b_arr[i];
  sort(a_arr,a_arr+n);
  sort(b_arr,b_arr+k);
  dp[0][0]=0;
  for(I i=0;i<n;i++)for(I j=0;j<=k;j++){
    if(j<k)cmb(dp[i+1][j+1],max(dp[i][j],abs(a_arr[i]-b_arr[j])+abs(p-b_arr[j])));
    if(j+1<=k)cmb(dp[i][j+1],dp[i][j]);
  }
  printf("%lli\n",*min_element(dp[n],dp[n]+k+1));
}