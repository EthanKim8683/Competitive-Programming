#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2e5;
const Lli X=1e13;
Lli a_arr[N];
I b_arr[N];
Lli icps[N];
priority_queue<pair<Lli,I>>ques;
I n,k;
B chk(Lli x){
  while(ques.size())ques.pop();
  copy_n(a_arr,n,icps);
  for(I i=0;i<n;i++)ques.push({-icps[i]/b_arr[i],i});
  for(I i=0;i<k;i++){
    auto[t,j]=ques.top();ques.pop();
    if(-t<i)return 0;
    ques.push({-(icps[j]+=x)/b_arr[j],j});
  }
  return 1;
}
Lli fnd(){
  Lli l=0,r=X;
  while(l<r){
    Lli m=l+(r-l)/2;
    chk(m)?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>b_arr[i];
  Lli res=fnd();
  printf("%lli\n",res==X?-1:res);
}
/*
we can binary search for the minimum value of x such that no laptop's charge
goes below zero at any point in time

at any given moment, the laptop whose charge will dip below zero first should
be charged, meaning we can greedily check for each x in this way
*/