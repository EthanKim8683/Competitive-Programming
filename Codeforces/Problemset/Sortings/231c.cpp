#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I a_arr[N];
Lli ps[N+1];
I k;
I fnd(I i){
  I l=0,r=i;
  while(l<r){
    I m=l+(r-l)/2;
    (Lli)a_arr[i]*(i-m)-(ps[i]-ps[m])<=k?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  for(I i=0;i<n;i++)ps[i+1]=ps[i]+a_arr[i];
  pair<I,I>res={0,0};
  for(I i=0;i<n;i++){
    I j=fnd(i);
    res=max(res,{i-j+1,-a_arr[i]});
  }
  auto[occ,val]=res;
  printf("%i %i\n",occ,-val);
}