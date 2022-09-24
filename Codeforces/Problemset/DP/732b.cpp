#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=500;
const I K=500;
const I MAX=1e9;

I a_arr[N];
I dp[N][K+1];
I pars[N][K+1];
vector<I>ress;

void add(I d,I i,I j,I k){
  if(d>=dp[i+1][j])return;
  dp[i+1][j]=d,pars[i+1][j]=k;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  fill(&dp[0][0],&dp[0][0]+N*(K+1),MAX);
  for(I i=a_arr[0];i<=max(a_arr[0],k);i++)dp[0][i]=i-a_arr[0];
  for(I i=0;i+1<n;i++)
    for(I j=a_arr[i];j<=max(a_arr[i],k);j++)
      for(I l=max(k-j,a_arr[i+1]);l<=max(a_arr[i+1],k);l++)
        add(dp[i][j]+l-a_arr[i+1],i,l,j);
  I j=k;
  for(I i=a_arr[n-1];i<=max(a_arr[n-1],k);i++)
    if(dp[n-1][i]<dp[n-1][j])j=i;
  I res=dp[n-1][j];
  for(I i=n-1;i>=0;i--){
    ress.push_back(j);
    j=pars[i][j];
  }
  reverse(ress.begin(),ress.end());
  printf("%i\n",res);
  for(auto i:ress)printf("%i ",i);
}