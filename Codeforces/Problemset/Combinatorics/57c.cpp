#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const Lli MOD=1e9+7;
Lli facs[2*N+1];
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
  for(I i=1;i<=2*N;i++)facs[i]=facs[i-1]*i%MOD;
  I n;cin>>n;
  printf("%lli\n",(2*bin(n+n-1,n-1)-n+MOD)%MOD);
}
/*
if we start off with an array containing only 1's, we can add 1 any number of
times before any element as long as the total number of 1's added does not
exceed n

this means we can use stars and bars to count the number and non-increasing
or non-decreasing arrays and subtract the overlap (arrays equal throughout)
*/