#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=100;
const I MAX=1e9;

I dp[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,d;cin>>n>>d;
  S s;cin>>s;
  fill_n(dp,n+1,MAX);
  if(s[0]=='1')dp[0]=0;
  for(I i=0;i<n;i++)
    for(I j=1;j<=d;j++)
      if(i+j<n&&s[i+j]=='1')dp[i+j]=min(dp[i+j],dp[i]+1);
  I res=dp[n-1];
  printf("%i\n",res==MAX?-1:res);
}