#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I M=2e5;
const I N=2e5;
const I K=2e5;
I a_arr[M];
tuple<I,I,I>trps[K];
I ps[N+1];
I m,n,k,t;
B chk(I a){
  fill_n(ps,n+1,0);
  for(I i=0;i<k;i++){
    auto[l,r,d]=trps[i];
    if(d<=a)continue;
    ps[l-1]++,ps[r]--;
  }
  for(I i=0;i<n;i++)ps[i+1]+=ps[i];
  I tot=n+1;
  for(I i=0;i<n;i++)tot+=2*!!ps[i];
  return tot<=t;
}
I fnd(){
  I l=0,r=m;
  while(l<r){
    I i=l+(r-l)/2;
    chk(a_arr[i])?r=i:l=i+1;
  }
  return m-l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>m>>n>>k>>t;
  for(I i=0;i<m;i++){
    I a;cin>>a;
    a_arr[i]=a;
  }
  for(I i=0;i<k;i++){
    I l,r,d;cin>>l>>r>>d;
    trps[i]={l,r,d};
  }
  sort(a_arr,a_arr+m);
  printf("%i\n",fnd());
}