#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const I N=1e5;
const Lli MAX=1e18;

Lli dp[N][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I a,b,p;cin>>a>>b>>p;
    S s;cin>>s;
    I n=s.size();
    reverse(s.begin(),s.end());
    for(I i=0;i<n;i++)dp[i][0]=dp[i][1]=MAX;
    if(s[1]=='A')dp[1][0]=a;
    if(s[1]=='B')dp[1][1]=b;
    for(I i=1;i+1<n;i++){
      if(s[i+1]=='A'){
        dp[i+1][0]=min(dp[i+1][0],dp[i][0]);
        dp[i+1][0]=min(dp[i+1][0],dp[i][1]+a);
      }
      if(s[i+1]=='B'){
        dp[i+1][1]=min(dp[i+1][1],dp[i][0]+b);
        dp[i+1][1]=min(dp[i+1][1],dp[i][1]);
      }
    }
    I res=0;
    for(I i=1;i<n;i++)if(min(dp[i][0],dp[i][1])<=p)res=i;
    printf("%i\n",n-res);
  }
}