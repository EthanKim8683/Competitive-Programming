#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;
struct Cow{I x,y;};

/*
lazy. didn't implement

all pairs are disjoint
you can skip up to 1 cow, and consecutively
if the first skipped cow can't reach the
second skipped cow
*/

const I N=1e5;
const I MAX=1e9,MIN=-1e9;

Cow cows[N];
I dp[N+1][2];
I n,k;

B bnd(I i,I j){
  return j<n?abs(cows[i].x-cows[j].x)<=k:0;
}

B cmp(Cow a,Cow b){
  return a.x<b.x;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t>>n>>k;
  fill_n(dp,n,t==2?MIN:MAX);
  for(I i=0;i<n;i++)cin>>cows[i].x>>cows[i].y;
  sort(cows,cows+n,cmp);
  for(I i=0;i<n;i++){
    auto[x1,y1]=cows[i];
  }
  return 0;
}