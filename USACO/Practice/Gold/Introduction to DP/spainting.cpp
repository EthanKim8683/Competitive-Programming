#include<iostream>
#include<cstdio>
#include<deque>

using namespace std;

using I=int;
using Lli=long long int;

/*
Without considering k, a canvas may have
m^n different paintings. However, with k
we must leave a contiguous range of the
same color with k length, representing
the topmost layer.

__       __        __      __       __
 __     __        __      __       __
  __      __     __      __       __
   __      __      __   __       __
    __      __      __      __  __
001234  100234  210034  321004  432100

With this method, any painting can be
produced as long as that contiguous range
(topmost layer) is present.

Now, you'd think that we could just do
m*(n-k+1)*(m^(n-k)), but you'd be wrong
because, consider the example input for
this problem: paintings AAA and BBB would
be counted twice!

Therefore, we have to fix this with a bit
of dp...
*/

const Lli MOD=1e9+7;

deque<Lli>dp;
Lli tot=0;

Lli pow(Lli x,Lli y){
  x%=MOD;
  Lli res=1;
  while(y){
    if(y&1)(res*=x)%=MOD;
    (x*=x)%=MOD;
    y>>=1;
  }
  return res;
}

void add(Lli val){
  (tot+=val)%=MOD;
  dp.push_back(val);
}

void mov(Lli val){
  (tot+=val-dp.front())%=MOD;
  dp.push_back(val);
  dp.pop_front();
}

I main(){
#ifndef ETHANKIM8683
  freopen("spainting.in","r",stdin);
  freopen("spainting.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  Lli cur=1;
  for(I i=1;i<k;i++)
    add((cur*=m)%=MOD);
  for(I i=k;i<=n;i++)
    mov(tot*(m-1)%MOD);
  Lli res=(pow(m,n)-dp.back())%MOD;
  printf("%lli\n",res+(res<0)*MOD);
  return 0;
}