#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I A=1e6;
const Lli MOD=1e9+7;
I a_arr[N];
Lli facs[A+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  return facs[n]*inv(facs[n-k]*facs[k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=A;i++)facs[i]=facs[i-1]*i%MOD;
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli res=1;
  for(I i=1;i<n;i++){
    I low=a_arr[i-1]/2,upp=a_arr[i]/2;
    if(upp<low)(res*=bin(low,upp))%=MOD;
    if(upp>low)(res*=bin(low-1+upp-low,upp-low))%=MOD;
  }
  printf("%lli\n",res);
}