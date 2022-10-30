#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=200000;

I a_arr[N];
Lli ps[N+1];
set<Lli>pres;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)ps[i+1]=a_arr[i];
  for(I i=0;i<n;i++)ps[i+1]+=ps[i];
  I res=0;
  for(I i=0;i<n;i++){
    if(pres.count(ps[i+1]))pres.clear(),res++;
    pres.insert(ps[i]);
  }
  printf("%i\n",res);
}