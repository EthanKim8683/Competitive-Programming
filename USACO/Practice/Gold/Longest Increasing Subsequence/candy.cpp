#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;
struct Can{I s,t;};

/*
Wagon count is length of LDS.

LDS based on if candies are able to be
connected.

Sort by time.
*/

const I N=100000;

Can cans[N];

B cmp(Can a,Can b){
  return a.t<b.t;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>cans[i].s>>cans[i].t;
  sort(cans,cans+n,cmp);
  for(I i=0;i<n;i++)printf("%i %i\n",cans[i].s,cans[i].t);
  return 0;
}