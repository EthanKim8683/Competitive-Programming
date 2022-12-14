#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=200000;
const Lli MAX=1e13;
I v_arr[N];
Lli sums[N];
Lli maxs[N];
Lli ress[N];
Lli tot;
B chk1(Lli i,Lli x){
  return (i+1)*x>=sums[i];
}
Lli fnd1(I i){
  Lli l=0,r=MAX;
  while(l<r){
    Lli m=l+(r-l)/2;
    chk1(i,m)?r=m:l=m+1;
  }
  return l;
}
B chk2(Lli i,Lli x){
  return (i+1)*x>=tot;
}
Lli fnd2(I i){
  Lli l=maxs[i],r=MAX;
  while(l<r){
    Lli m=l+(r-l)/2;
    chk2(i,m)?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>v_arr[i];
  copy_n(v_arr,n,sums);
  for(I i=0;i+1<n;i++)sums[i+1]+=sums[i];
  for(I i=0;i<n;i++)maxs[i]=fnd1(i);
  for(I i=0;i+1<n;i++)maxs[i+1]=max(maxs[i+1],maxs[i]);
  tot=accumulate(v_arr,v_arr+n,0ll);
  for(I i=0;i<n;i++)ress[i]=-fnd2(i);
  I q;cin>>q;
  while(q--){
    I t;cin>>t;
    I j=lower_bound(ress,ress+n,-t)-ress;
    printf("%i\n",j==n?-1:j+1);
  }
}