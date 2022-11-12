#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;
const I MAX=1e9;

I a_arr[N];
I ps[N+1];
I n,s;

I fnd(I i){
  I l=i+1,r=n;
  while(l<r){
    I m=l+(r-l+1)/2;
    if(ps[m]-ps[i]<=s)l=m;
    else r=m-1;
  }
  if(ps[l]-ps[i]!=s)return MAX;
  return i+n-l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n>>s;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)ps[i+1]=a_arr[i];
    for(I i=0;i<n;i++)ps[i+1]+=ps[i];
    I res=MAX;
    for(I i=0;i<n;i++)res=min(res,fnd(i));
    printf("%i\n",res==MAX?-1:res);
  }
}