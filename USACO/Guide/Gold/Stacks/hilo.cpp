#include<iostream>
#include<cstdio>
#include<set>
#include<map>

using namespace std;

using I=int;
using Lli=long long int;

/*
HILOs in one range may branch to other ranges
within it. e.g. 1-5 has 2 HILOs, so 1-2 and
3-4 will have >=2 HILOs.

For each x, find the greatest visited value y
where y<x and least visited value z where x<z
and create ranges (y,x) and (x,z).

For each range, keep track of the last updated
end and add a HILO if it goes from HI end to
LO end.
*/

const I N=2e5;

I prms[N];
set<I>viss;
map<pair<I,I>,pair<I,I>>rngs;
I ress[N+1];

void add(I i,I j,I tot,I sid){
  if(j-i>1)rngs.insert({{i,j},{tot,sid}});
  else ress[i]=tot;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>prms[i];
  viss.insert(0);
  viss.insert(n+1);
  add(0,n+1,0,-1);
  for(I i=0;i<n;i++){
    I x=prms[i];
    auto it=viss.upper_bound(x);
    I z=*it--;
    I y=*it;
    auto[tot,sid]=rngs.find({y,z})->second;
    add(y,x,tot,0);
    add(x,z,tot+(sid==0),1);
    viss.insert(x);
  }
  for(I i=0;i<=n;i++)printf("%i\n",ress[i]);
  return 0;
}