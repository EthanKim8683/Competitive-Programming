#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I X=1e9;

I a_arr[N];
I n,k;

B chk(I x){
  I cnt=0,las=0,dia=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(a*2<x){
      if(++cnt>k)return false;
      dia=max(dia,min(X,las)),las=X;
    }else
      dia=max(dia,min(a,las)),las=a;
  }
  if(cnt==k)return dia>=x;
  if(k>1)return true;
  for(I i=0;i<n;i++)
    if(a_arr[i]>=x)return true;
  return false;
}

I fnd(){
  I l=0,r=X;
  while(l<r){
    I m=l+(r-l+1)/2;
    if(chk(m))l=m;
    else r=m-1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    printf("%i\n",fnd());
  }
  return 0;
}