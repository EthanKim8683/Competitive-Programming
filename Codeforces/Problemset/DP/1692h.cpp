#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=2e5;

I x_arr[N];
map<I,vector<I>>gams;
I dp[N],pars[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>x_arr[i];
    gams.clear();
    for(I i=0;i<n;i++)gams[x_arr[i]].push_back(i);
    fill_n(dp,n,1),fill_n(pars,n,-1);
    for(I i=0;i<n;i++){
      I x=x_arr[i];
      auto it=upper_bound(gams[x].begin(),gams[x].end(),i);
      if(it==gams[x].end())continue;
      I j=*it;
      if(dp[i]+1-(j-i-1)<=dp[j])continue;
      dp[j]=dp[i]+1-(j-i-1),pars[j]=i;
    }
    I j=max_element(dp,dp+n)-dp,i=j;
    while(pars[i]!=-1)i=pars[i];
    printf("%i %i %i\n",x_arr[j],i+1,j+1);
  }
}