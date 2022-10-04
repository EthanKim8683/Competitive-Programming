#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using C=char;

const I N=1e6;
const I MAX=1e9;

I dp[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S a;cin>>a;
  S b;cin>>b;
  fill_n(dp,n+1,MAX);
  dp[0]=0;
  for(I i=0;i<n;i++){
    if(i+1<n){
      C c=a[i],d=a[i+1];
      C e=b[i],f=b[i+1];
      if(c!=e&&d!=f&&c!=d)dp[i+2]=min(dp[i+2],dp[i]+1);
    }
    dp[i+1]=min(dp[i+1],dp[i]+(a[i]!=b[i]));
  }
  printf("%i\n",dp[n]);
}