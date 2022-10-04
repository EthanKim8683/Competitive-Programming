#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
struct Tem{I p,t;};

const I N=50;

Tem tems[N];

bool operator<(Tem a,Tem b){
  if(a.p>b.p)return 1;
  if(a.p==b.p&&a.t<b.t)return 1;
  return 0;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k,k--;
  for(I i=0;i<n;i++)cin>>tems[i].p>>tems[i].t;
  sort(tems,tems+n);
  auto low=lower_bound(tems,tems+n,tems[k]);
  auto upp=upper_bound(tems,tems+n,tems[k]);
  printf("%i\n",upp-low);
}