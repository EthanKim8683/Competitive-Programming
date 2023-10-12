#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200000;
const I LOGN=18;
I a_arr[N];
I spas[N][LOGN];
map<I,I>pres;
I qry(I l,I r){
  I d=31-__builtin_clz(r-l);
  return spas[l][d]|spas[r-(1<<d)][d];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)spas[i][0]=a_arr[i];
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<i)<=n;j++)spas[j][i]=spas[j][i-1]|spas[j+(1<<(i-1))][i-1];
  auto lft=[&](I i){
    I a=a_arr[i],l=pres[a],r=i;
    while(l<r){
      I m=l+(r-l)/2;
      qry(m,i+1)==a?r=m:l=m+1;
    }
    return l;
  };
  auto rgt=[&](I i){
    I a=a_arr[i],l=i,r=n-1;
    while(l<r){
      I m=l+(r-l+1)/2;
      qry(i,m+1)==a?l=m:r=m-1;
    }
    return l;
  };
  Lli res=(Lli)n*(n-1)/2;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    res-=(Lli)(i-lft(i)+1)*(rgt(i)-i+1)-1;
    pres[a]=i+1;
  }
  printf("%lli\n",res);
}
/*
for each mountain, we can count the number of positions to the left and right
such that the bitwise or of the mountains between either position and the
mountain itself (inclusive) remains equals to the mountain

using this, we can count the number of invalid ranges as any pairing of the
left and right positions will result in a bitwise or equal to the mountain
in question

to handle the edge case where two mountains of same height invalidate
overlapping sets of pairs of left and right positions, we can clamp the
leftmost position of each mountain to strictly after the last occurrence of a
mountain of equal height
*/