#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=1.5e5;

I a_arr[N];
Lli ps[N+1];
I n;
I x;

B chk(I v){
  return ps[v]>=x;
}

I fnd(){
  I l=0,r=n+1;
  while(l<r){
    I m=l+(r-l)/2;
    if(chk(m))r=m;
    else l=m+1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I q;cin>>n>>q;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n,greater<I>());
    for(I i=0;i<n;i++)ps[i+1]=a_arr[i];
    for(I i=0;i<n;i++)ps[i+1]+=ps[i];
    while(q--){
      cin>>x;
      I res=fnd();
      printf("%i\n",res==n+1?-1:res);
    }
  }
}