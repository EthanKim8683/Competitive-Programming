#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=500000;
const I C=200000;
const Lli MOD=1e6+3;
Lli facs[N+C+1];
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
  for(I i=1;i<=N+C;i++)facs[i]=facs[i-1]*i%MOD;
  I n,c;cin>>n>>c;
  printf("%lli\n",(bin(n+c,c)+MOD-1)%MOD);
}
/*
stars and bars
*/