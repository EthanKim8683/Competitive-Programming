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
  I n,m;cin>>n>>m;
  printf("%lli\n",mpw(mpw(2,m)-1,n));
}
/*
each kind of present can choose any non-empty subset of boxes
*/