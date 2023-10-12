#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I LOGY=60;
Lli n;
Lli cnt(Lli y){
  Lli res=0;
  for(I i=0;(y<<i)<=n;i++)res+=min(n-(y<<i)+1,(1ll<<i)<<(~y&1));
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli k;cin>>n>>k;
  Lli y=0;
  for(I i=LOGY-1;i>=0;i--)y|=(Lli)(cnt(y|1ll<<i)>=k)<<i;
  printf("%lli\n",y);
}
/*
for each y, the number of path(x) containing y is the number of x in [1, n]
such that y >> 1 is a prefix of x and, if y & 1 = 1, so is y

we can construct y greedily bit-by-bit, setting bits if the number of path(x)
does not subceed k in doing so
*/