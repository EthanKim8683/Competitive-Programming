#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=3e5;
I d_arr[N];
pair<I,I>rngs[N];
I k;
pair<I,I>cmb(pair<I,I>a,pair<I,I>b){
  auto[l1,r1]=a;auto[l2,r2]=b;
  if(r1-2*k>=l2)return{l2,r2};
  return{max(l1,l2),r2};
}
pair<I,I>fix(pair<I,I>a){
  auto[l,r]=a;
  if(r==2*k-1)return{0,2*k-1};
  return{l,r};
}
pair<I,I>inc(pair<I,I>a){
  auto[l,r]=a;
  return{l+1,r+1};
}
B vld(pair<I,I>a){
  auto[l,r]=a;
  return l<=r;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,l;cin>>n>>k>>l;
    for(I i=0;i<n;i++)cin>>d_arr[i];
    for(I i=0;i<n;i++){
      I d=d_arr[i];
      rngs[i]={max(k-1-(l-d),0),min(k-1+(l-d),2*k-1)};
    }
    pair<I,I>cur={0,2*k-1};
    B res=1;
    for(I i=0;i<n;i++){
      cur=fix(cmb(inc(cur),rngs[i]));
      res&=vld(cur);
      auto[l,r]=cur;
    }
    printf("%s\n",res?"Yes":"No");
  }
}