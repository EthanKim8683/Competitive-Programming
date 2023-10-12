#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e7;
const I K=5;
const Lli MOD=998244353;
Lli facs[N+1];
Lli a_arr[N+1];
Lli dp[K+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  if(n<0||k<0||n-k<0)return 0;
  return facs[n]*inv(facs[k]*facs[n-k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I n;Lli a1,x,y,m;I k;cin>>n>>a1>>x>>y>>m>>k;
  a_arr[1]=a1;
  for(I i=2;i<=n;i++)a_arr[i]=(a_arr[i-1]*x+y)%m;
  Lli res=0,cur=0;
  for(I i=1;i<=n;i++){
    for(I j=k-1;j>=0;j--)(dp[j]+=dp[j+1])%=MOD;
    for(I j=0;j<=k;j++){
      I l=i-k+1;
      if(l>=1&&l<=i-j)(dp[j]+=a_arr[l])%=MOD;
    }
    (cur+=dp[0])%=MOD;
    res^=cur*i;
  }
  printf("%lli\n",res);
}
/*
note that, by Pascal's triangle, bin(n, k) = bin(n - 1, k) + bin(n - 1, k - 1)

with this, we can keep track of the relevant k values of Pascal's triangle
(which we update according to the current index) to modify previous b[i] to
solve for b[i + 1]
*/