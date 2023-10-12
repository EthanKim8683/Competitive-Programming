#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=200000;
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
  return facs[n]*inv(facs[k]*facs[n-k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  S s;cin>>s;
  Lli res=0;
  I low=0,upp=0;
  for(auto c:s)upp+=c==')';
  for(auto c:s){
    if(c=='(')low++;
    if(c==')')upp--,(res+=bin(low+upp,upp+1))%=MOD;
  }
  printf("%lli\n",res);
}
/*
at each ")", we can treat the current ")" as the first ")" in the subsequence

then, using the number of "(" and ")" before and after it, respectively, we
can calculate the number of regular simple bracket subsequences

let n equal the number of "(" before, and m the number of ")" after

we can represent the summation of the number of ways to choose k brackets
from either set as the summation of bin(n, k) * bin(m, k - 1) for all k in
[1, min(n, m + 1)]

since we are looking at a summation of a product of binomials, we could try
to convert this to a single binomial using Vandermonde's identity

first, if k < 0 or k > min(n, m + 1), at least one of the binomials will
evaluate to 0, so we can represent the earlier summation as the sum of
bin(n, k) * bin(m, k - 1) for all k in [0, m + 1]

then, bin(m, k - 1) can be become bin(m, m - (k - 1)), since they both
expand to m! / ((k - 1)! * (m - (k - 1))!)

finally, our summation bin(n, k) * bin(m, m + 1 - k) can be simplified to the
binomial bin(n + m, m + 1)
*/