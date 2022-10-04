#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

I w_arr[N];
Lli ps[N+1];

I fnd(I l,I r,Lli x){
  while(l<=r){
    I m=l+(r-l)/2;
    Lli sum=ps[m];
    if(sum==x)return m;
    if(sum<x)l=m+1;
    if(sum>x)r=m-1;
  }
  return -1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>w_arr[i];
    for(I i=0;i<n;i++)ps[i+1]=w_arr[i];
    for(I i=0;i<n;i++)ps[i+1]+=ps[i];
    Lli sum=0;
    I res=0;
    for(I i=n-1;i>=0;i--){
      sum+=w_arr[i];
      I j=fnd(0,i,sum);
      if(j!=-1)res=max(res,j+(n-i));
    }
    printf("%i\n",res);
  }
}