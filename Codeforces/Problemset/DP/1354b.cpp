#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=200000;
const I MAX=1e9;

set<I>inds[3];
I dp[N][1<<3];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    for(I i=0;i<n;i++)for(I j=0;j<(1<<3);j++)dp[i][j]=MAX;
    for(I i=0;i<3;i++)inds[i].clear();
    for(I i=0;i<n;i++)inds[s[i]-'1'].insert(i);
    for(I i=0;i<n;i++)dp[i][1<<(s[i]-'1')]=1;
    for(I i=0;i<n;i++)for(I j=0;j<(1<<3);j++){
      for(I k=0;k<3;k++){
        if(!(j>>k&1)){
          auto it=inds[k].upper_bound(i);
          if(it!=inds[k].end())dp[*it][j|1<<k]=min(dp[*it][j|1<<k],dp[i][j]+*it-i);
        }
      }
    }
    I res=MAX;
    for(I i=0;i<n;i++)res=min(res,dp[i][(1<<3)-1]);
    printf("%i\n",res==MAX?0:res);
  }
}