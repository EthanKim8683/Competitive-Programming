#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
Lli a_arr[N];
Lli segs[2*N];
I k;
Lli gcd(Lli a,Lli b){
  return b?gcd(b,a%b):a;
}
void asn(I i,Lli val){
  segs[i+k]=val;
}
void bld(){
  for(I i=k-1;i>0;i--)segs[i]=gcd(segs[i<<1],segs[i<<1|1]);
}
Lli qry(I l,I r){
  Lli res=0;
  for(l+=k,r+=k;l<r;l>>=1,r>>=1){
    if(l&1)res=gcd(res,segs[l++]);
    if(r&1)res=gcd(res,segs[--r]);
  }
  return res;
}
I fnd(I i){
  I l=i,r=k;
  while(l<r){
    I m=l+(r-l+1)/2;
    qry(i,m)>1?l=m:r=m-1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    k=n-1;
    for(I i=0;i<k;i++)asn(i,abs(a_arr[i+1]-a_arr[i]));
    bld();
    I res=1;
    for(I i=0;i<k;i++)res=max(res,fnd(i)-i+1);
    printf("%i\n",res);
  }
}