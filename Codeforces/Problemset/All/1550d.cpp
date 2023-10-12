#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const Lli MOD=1e9+7;
Lli facs[N+1];
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
  return facs[n]*inv(facs[n-k]*facs[k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I t;cin>>t;
  while(t--){
    I n,l,r;cin>>n>>l>>r;
    Lli res=0;
    auto slv=[&](I low,I upp){
      for(I i=0;i<low;i++)(res+=bin((n-i-1)-max(r+l-(n-1-i)-2,0),low-i)*(r-(n-1-i)-1))%=MOD;
      for(I i=0;i<upp;i++)(res+=bin(min(r+l-i-2,n)-(i+1),upp-i)*(i+1-l))%=MOD;
      (res+=min(upp+1-l,r-(n-1-low)-1))%=MOD;
    };
    slv(n/2,n-n/2);
    if(n%2==1)slv(n-n/2,n/2);
    printf("%lli\n",(res+MOD)%MOD);
  }
}
/*
we can rewrite the pairwise condition of F(a) as follows:
a[i] + a[j] = i + j
a[i] - i = -(a[j] - j)

and, to produce maximum possible F(a), half of all a[i] - i should equal +x,
while the remaining a[j] - j should equal -x (such that x != 0, since x must
not be 0 for a to be good)

therefore, to count the number of excellent arrays a, we can start with
a[i] = i for all i, assign half to +x and half to -x then count the number of
x (excluding x = 0) possible among all assignments

since the number of x is equal to the minimum of (i + 1) - l and r - (j + 1)
such that i is the minimum of the -x set and j is the maximum of the +x set,
we can use combinatorics to find the number of arrangements such that
(i + 1) - l is the minimum for all i or r - (j + 1) is the minimum for all j
*/