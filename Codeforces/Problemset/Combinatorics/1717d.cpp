#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
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
  return facs[n]*inv(facs[k]*facs[n-k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I n,k;cin>>n>>k;
  Lli res=mpw(2,n);
  for(I i=k+1;i<=n;i++)(res-=bin(n,i))%=MOD;
  printf("%lli\n",(res+MOD)%MOD);
}
/*
we can "hide" the largest values in subtrees that take more than k changes
to reach

there are bin(n, i) such positions where i is in [k + 1, n]
*/