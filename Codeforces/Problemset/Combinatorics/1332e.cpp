#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const Lli MOD=998244353;
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
  I n,m,l,r;cin>>n>>m>>l>>r;
  Lli cnt=(Lli)n*m,rng=r-l+1,res;
  if(cnt%2==1){
    res=mpw(rng,cnt);
  }else if(cnt%2==0){
    res=mpw(rng,cnt);
    if(rng%2==1)(res+=1)%=MOD;
    (res*=inv(2))%=MOD;
  }
  printf("%lli\n",res);
}
/*
each operation changes the parity of an even number of cells at a time, and
since, if all cells are of the same parity, operations of the first type can be
used to make all cells the same height, as long as an initial grid has an even
amount of at least one parity, the Player can accomplish their goal

if n * m is odd, all initial grids will have an even number of one parity and
an odd number of the other, so all initial grids satisfy the Player's
requirement

if n * m is even, if r - l + 1 is even, half of the grids have an even number
of each parity, otherwise there is exactly one more initial grid with an even
number of each parity
*/