#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=5000;
const Lli MAX=1e18;
I a_arr[N];
Lli dp[2][N];
vector<I>cpss;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cpss.push_back(a_arr[i]);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<cpss.size();i++)dp[0][i]=abs(cpss[i]-a_arr[0]);
  for(I i=1;i<n;i++){
    I j=lower_bound(cpss.begin(),cpss.end(),a_arr[i])-cpss.begin();
    Lli pre=MAX;
    for(I k=0;k<=j;k++){
      pre=min(pre,dp[(i-1)%2][k]);
      dp[i%2][k]=pre+cpss[j]-cpss[k];
    }
    for(I k=j;k<cpss.size();k++){
      pre=min(pre,dp[(i-1)%2][k]);
      dp[i%2][k]=pre+cpss[k]-cpss[j];
    }
  }
  printf("%lli\n",*min_element(dp[(n-1)%2],dp[(n-1)%2]+cpss.size()));
}