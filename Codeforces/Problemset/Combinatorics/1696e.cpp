#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I A=2e5;
const Lli MOD=1e9+7;
Lli facs[N+A+1];
I a_arr[N+1];
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
  for(I i=1;i<=N+A;i++)facs[i]=facs[i-1]*i%MOD;
  I n;cin>>n;
  for(I i=0;i<n+1;i++)cin>>a_arr[i];
  Lli res=0;
  for(I i=0;i<n+1;i++)(res+=bin(i+a_arr[i],a_arr[i]-1))%=MOD;
  printf("%lli\n",res);
}
/*
we can think of the problem as a rotated Pascal's triangle, where each white
cell contributes bin(i + j, j) operations, where (i, j) are the coordinates of
the cell

this means each row contributes bin(i + a[i], a[i] - 1) operations by the
hockey-stick identity
*/