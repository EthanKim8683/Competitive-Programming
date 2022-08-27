#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using Lli=long long int;

const Lli MOD=1e9+7;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  Lli p=1,t=1;
  for(I i=1;i<=n;i++)(p*=i)%=MOD;
  for(I i=1;i<n;i++)(t*=2)%=MOD;
  (p-=t)%=MOD;
  printf("%lli\n",(p+MOD)%MOD);
  return 0;
}