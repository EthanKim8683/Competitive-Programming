#include<bits/stdc++.h>
 
using namespace std;
 
using I=int;
using Lli=long long int;
using B=bool;
 
const I N=2e6;
const I M=1e5;
const I X=2000;
 
I w_arr[M];
I n;
 
B chk(I x){
  if(x%2)return x*(x-1)/2+1<=n;
  return x*x/2<=n;
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
  I m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I q,w;cin>>q>>w;
    w_arr[i]=w;
  }
  sort(w_arr,w_arr+m,greater<I>());
  I x=fnd();
  Lli res=0;
  for(I i=0;i<min(x,m);i++)res+=w_arr[i];
  printf("%lli\n",res);
}