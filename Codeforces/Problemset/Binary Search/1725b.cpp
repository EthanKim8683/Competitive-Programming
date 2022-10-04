#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=1e5;

I p_arr[N];
I n,d;

B chk(I x){
  I rem=n-x;
  for(I i=0;i<x;i++){
    I p=p_arr[i];
    I sum=p;
    while(sum<=d){
      sum+=p,rem--;
      if(rem<0)return 0;
    }
  }
  return 1;
}

I fnd(){
  I l=0,r=n;
  while(l<r){
    I m=l+(r-l+1)/2;
    if(chk(m))l=m;
    else r=m-1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>d;
  for(I i=0;i<n;i++)cin>>p_arr[i];
  sort(p_arr,p_arr+n,greater<I>());
  printf("%i\n",fnd());
}