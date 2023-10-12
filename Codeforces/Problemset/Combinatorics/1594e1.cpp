#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const Lli MOD=1e9+7;
Lli mpw(Lli x,Lli y,Lli m){
  Lli res=1;
  for(x%=m;y;y>>=1,(x*=x)%=m)if(y&1)(res*=x)%=m;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>k;
  printf("%lli\n",6*mpw(4,(mpw(2,k,MOD-1)-2+MOD-1)%(MOD-1),MOD)%MOD);
}
/*
each color has exactly 4 neighboring colors, meaning each child can be one of
4 colors (the root can be any of 6 colors) for a total of 6 * 4 ^ (2 ^ k - 2)
*/