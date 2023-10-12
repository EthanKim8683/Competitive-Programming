#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I a_arr[N];
Lli segs[2*N];
I n;
void asn(I i,Lli val){
  segs[i+n]=val;
}
void upd(I l,I r,Lli val){
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)segs[l++]+=val;
    if(r&1)segs[--r]+=val;
  }
}
Lli qry(I i){
  Lli res=0;
  for(i+=n;i>0;i>>=1)res+=segs[i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)asn(i,a_arr[i]);
  Lli res=a_arr[0];
  for(I i=0;i+1<n;i++)res+=max(a_arr[i+1]-a_arr[i],0);
  printf("%lli\n",(res+(res>0))/2);
  I q;cin>>q;
  while(q--){
    I l,r,x;cin>>l>>r>>x,l--,r--;
    res-=qry(0);
    if(l-1>=0)res-=max(qry(l)-qry(l-1),0ll);
    if(r+1<n)res-=max(qry(r+1)-qry(r),0ll);
    upd(l,r+1,x);
    res+=qry(0);
    if(l-1>=0)res+=max(qry(l)-qry(l-1),0ll);
    if(r+1<n)res+=max(qry(r+1)-qry(r),0ll);
    printf("%lli\n",(res+(res>0))/2);
  }
}