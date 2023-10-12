#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=150000;
const Lli MOD=998244353;
I a_arr[2*N];
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
  return facs[n]*inv(facs[n-k]*facs[k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<2*n;i++)cin>>a_arr[i];
  facs[0]=1;
  for(I i=1;i<=2*n;i++)facs[i]=facs[i-1]*i%MOD;
  sort(a_arr,a_arr+2*n);
  Lli dif=0;
  for(I i=n;i<2*n;i++)(dif+=a_arr[i])%=MOD;
  for(I i=0;i<n;i++)(dif-=a_arr[i])%=MOD;
  (dif*=bin(2*n,n))%=MOD;
  printf("%lli\n",(dif+MOD)%MOD);
}