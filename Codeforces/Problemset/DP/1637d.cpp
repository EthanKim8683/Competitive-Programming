#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=100;
const I A=100;
const I B=100;
const Lli MAX=1e18;

I a_arr[N];
I b_arr[N];
Lli dp[N+1][N*(A+B)+1];

void cmb(Lli&a,Lli b){
  a=min(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<=n;i++)for(I j=0;j<=n*(A+B);j++)dp[i][j]=MAX;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)cin>>b_arr[i];
    dp[0][0]=0;
    for(I i=0;i<n;i++){
      Lli a=a_arr[i],b=b_arr[i];
      dp[0][0]+=(a*a+b*b)*(n-1);
    }
    I sum=0;
    for(I i=0;i<n;i++){
      Lli a=a_arr[i],b=b_arr[i];
      for(I j=0;j<=sum;j++){
        cmb(dp[i+1][j+a],dp[i][j]+2*(j*a+(sum-j)*b));
        cmb(dp[i+1][j+b],dp[i][j]+2*(j*b+(sum-j)*a));
      }
      sum+=a+b;
    }
    printf("%lli\n",*min_element(dp[n],dp[n]+sum));
  }
}