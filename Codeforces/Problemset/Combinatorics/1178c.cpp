#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const Lli MOD=998244353;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I w,h;cin>>w>>h;
  Lli res=1;
  for(I i=0;i<w+h;i++)(res*=2)%=MOD;
  printf("%lli\n",res);
}
/*
given a tile, there are two ways to assign a tile to the right of it, both
ways with the same right border color

similarly, there are two ways to assign a tile to the bottom of a tile and
both ways have the same bottom border color

now, given a tile above and a tile to the left, there is only one choice of
tile since two border colors are given and exactly one tile satisfies each
pair of border colors

therefore, we can say there are 2 ^ w first-row tile combinations, then 2 ^ h
subsequent-row tile combinations in response

therefore, there are 2 * (w + h) tile combinations in total
*/