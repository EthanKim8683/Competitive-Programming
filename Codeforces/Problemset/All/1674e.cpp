#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I MAX=1e9;
I vals[N];
I a_arr[N];
B chk(I a,I b,I x){
  I y=(a-x+1)/2;
  return y+2*x>=b;
}
I fnd(I a,I b){
  I l=0,r=a;
  while(l<r){
    I m=l+(r-l)/2;
    chk(a,b,m)?r=m:l=m+1;
  }
  if(!chk(a,b,l))return MAX;
  return l+(a-l+1)/2;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  copy_n(a_arr,n,vals);
  sort(vals,vals+n);
  I res=(vals[0]+1)/2+(vals[1]+1)/2;
  for(I i=0;i+1<n;i++){
    I a=a_arr[i],b=a_arr[i+1];
    res=min(res,fnd(a,b)),res=min(res,fnd(b,a));
  }
  for(I i=1;i+1<n;i++){
    I a=a_arr[i-1],b=a_arr[i+1],c=min(a,b),d=max(a,b);
    res=min(res,d);
    res=min(res,(d-c+1)/2+c);
  }
  printf("%i\n",res);
}