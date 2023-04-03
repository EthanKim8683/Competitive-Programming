#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const Lli MOD=1e9+7;
Lli facs[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    Lli res=facs[n];
    (res*=n)%=MOD;
    (res*=n-1)%=MOD;
    printf("%lli\n",res);
  }
}