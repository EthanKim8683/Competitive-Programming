#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I N=2e5;

I d_arr[N];
Lli ps[N+1];
I n;

B fnd(I l,Lli tar){
  I r=n;
  while(l<=r){
    I m=l+(r-l)/2;
    Lli cur=ps[n]-ps[m];
    if(cur==tar)return 1;
    if(cur<tar)r=m-1;
    if(cur>tar)l=m+1;
  }
  return 0;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>d_arr[i];
  for(I i=0;i<n;i++)ps[i+1]=d_arr[i];
  for(I i=0;i<n;i++)ps[i+1]+=ps[i];
  Lli res=0;
  for(I i=0;i<n;i++){
    Lli cur=ps[i];
    if(fnd(i,cur))res=cur;
  }
  printf("%lli\n",res);
}