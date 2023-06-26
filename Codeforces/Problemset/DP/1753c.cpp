#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200000;
const Lli MOD=998244353;
I a_arr[N];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I bor=n-accumulate(a_arr,a_arr+n,0),cnt=bor-accumulate(a_arr,a_arr+bor,0);
    Lli res=0;
    for(I i=1;i<=bor-cnt;i++)(res+=inv((Lli)i*i))%=MOD;
    (res*=(Lli)n*(n-1)/2)%=MOD;
    printf("%lli\n",res);
  }
}