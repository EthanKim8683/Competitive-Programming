#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const Lli MOD=998244353;
I a_arr[N];
Lli dp[N+1][2];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  dp[0][0]=1;
  for(I i=1;i<=n;i++){
    (dp[i][1]+=dp[i-1][0]*(k-1)%MOD*inv(k-1))%=MOD;
    (dp[i][1]+=dp[i-1][1]*(k-2))%=MOD;
    (dp[i][0]+=dp[i-1][1]*(k-1))%=MOD;
  }
  auto cnt=[&](I t){
    Lli res=1;
    I j=-1,i=t;
    for(;i<n;i+=2){
      I a=a_arr[i];
      if(a==-1)continue;
      if(j!=-1){
        (res*=dp[(i-j)/2][a!=a_arr[j]])%=MOD;
      }else{
        (res*=mpw(k-1,(i-t)/2))%=MOD;
      }
      j=i;
    }
    if(j!=-1){
      (res*=mpw(k-1,(i-2-j)/2))%=MOD;
    }else{
      (res*=k*mpw(k-1,(i-2)/2)%MOD)%=MOD;
    }
    return res;
  };
  printf("%lli\n",cnt(0)*cnt(1)%MOD);
}
/*
an array is bad if, for any i < n - 2, b[i] == b[i + 2]

using dynamic programming we can count the number of arrays with elements in
[1, k] such that b[i] != b[i + 1] and the final element either does or doesn't
equal the first one

with this we can fill in the gaps between known elements of a for both
(disjoint) sets of indices of either parity
*/