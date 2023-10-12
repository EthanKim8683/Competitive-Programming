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
  Lli n,m;I k;cin>>n>>m>>k;
  printf("%lli\n",k==-1&&n%2!=m%2?0:mpw(mpw(2,m-1),n-1));
}
/*
we can set each row before the last to any combination of 1 and -1's such that
their product is k

the parity (even or odd) of the number of columns with incorrect parity (-1 or
1) will always be odd if k = -1 and even if k = 1

this is because, between two rows of same parity (-1 or 1), an even number of
(-1, 1) and (1, -1) pairs will always exist so the parity (even or odd) of the
number of columns with incorrect parity can never change

since the parity (even or odd) of the number of columns needing correction is
always proprotional to k, regardless of the contents of the other rows, the
final row can always ensure the field is valid
*/