#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I N=2e5;

I a_arr[N];
Lli ps[N+1];
I x;

B chk(Lli v,I j){
  if(v==0)return 0<=x;
  return ps[j]+(j+1)*(v-1)<=x;
}

I fnd(I j){
  I l=0,r=x;
  while(l<r){
    I m=l+(r-l+1)/2;
    if(chk(m,j))l=m;
    else r=m-1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n>>x;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    for(I i=0;i<n;i++)ps[i]=a_arr[i];
    for(I i=0;i+1<n;i++)ps[i+1]+=ps[i];
    Lli res=0;
    for(I i=0;i<n;i++)res+=fnd(i);
    printf("%lli\n",res);
  }
}