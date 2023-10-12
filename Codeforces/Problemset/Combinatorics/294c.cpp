#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1000;
const Lli MOD=1e9+7;
Lli facs[N+1];
I inds[N];
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
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>inds[i];
  sort(inds,inds+m);
  Lli res=1;
  for(I i=0;i+1<m;i++)if(inds[i+1]-inds[i]>=2)(res*=mpw(2,inds[i+1]-inds[i]-2))%=MOD;
  (res*=facs[n-m])%=MOD;
  for(I i=0;i+1<m;i++)(res*=inv(facs[inds[i+1]-inds[i]-1]))%=MOD;
  (res*=inv(facs[inds[0]-1]))%=MOD;
  (res*=inv(facs[n-inds[m-1]]))%=MOD;
  printf("%lli\n",res);
}
/*
we can solve for the switched-off lights between different switched-on lights
independently

at each step, Shaass can either turn on the light adjacent to the left or
right-sided lights

on the final step, the light is the same on either side, so there is only
one way to turn on that light

then, combining independent cases can be done by finding the number of ways
to choose indices for moves of the first case, second case, third case etc.
*/