#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=3e5;
const I V=1e9;
I v_arr[N];
I fens[N+1];
I n,k;
void upd(I i,I val){
  for(;i<=n;i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
B chk(I t){
  fill_n(fens,n+1,0);
  upd(0+1,1);
  B res;
  for(I i=k-1;i<n;i++){
    I j=lower_bound(v_arr,v_arr+n,v_arr[i]-t)-v_arr;
    upd(i+2,res=qry(i-k+2)-qry(j)>0);
  }
  return res;
}
I fnd(){
  I l=0,r=V;
  while(l<r){
    I m=l+(r-l)/2;
    chk(m)?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>k;
  for(I i=0;i<n;i++)cin>>v_arr[i];
  sort(v_arr,v_arr+n);
  printf("%i\n",fnd());
}