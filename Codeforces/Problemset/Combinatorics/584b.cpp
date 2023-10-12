#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const Lli MOD=1e9+7;
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  printf("%lli\n",(mpw(27,n)-mpw(7,n)+MOD)%MOD);
}
/*
since each i is independent, we can use the principle of inclusion-exclusion
to find the number of numberings such that at least one a[i] + a[i + n] +
a[i + 2 * n] != 6
*/