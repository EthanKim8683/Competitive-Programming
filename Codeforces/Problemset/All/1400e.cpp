#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=5000;
const I MAX=1e9;
I a_arr[N];
I dp[N+1][N+1];
vector<I>cpss;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*(N+1),MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  cpss.push_back(0);
  for(I i=0;i<n;i++)cpss.push_back(a_arr[i]);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  dp[0][0]=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i],k=lower_bound(cpss.begin(),cpss.end(),a)-cpss.begin();
    I pre=MAX;
    for(I j=0;j<=k;j++){
      pre=min(pre,dp[i][j]-cpss[j]);
      dp[i+1][j]=min(dp[i+1][j],pre+cpss[j]+(k!=j));
    }
    pre=MAX;
    for(I j=cpss.size()-1;j>=0;j--){
      pre=min(pre,dp[i][j]);
      if(j<=k)dp[i+1][j]=min(dp[i+1][j],pre+(k!=j));
    }
  }
  printf("%i\n",*min_element(dp[n],dp[n]+cpss.size()));
}