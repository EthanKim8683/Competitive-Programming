#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I LOGN=17;
const I FIXN=1<<LOGN;
const Lli MIN=-1e18;
I a_arr[N];
Lli vals[2*FIXN],dels[2*FIXN];
I siz(I i){
  return 1<<(__builtin_clz(i)-31+LOGN);
}
void app(I i,Lli val){
  vals[i]+=val;
  if(i<FIXN)dels[i]+=val;
}
void pll(I i){
  for(i+=FIXN;i>>=1;)vals[i]=max(vals[i<<1],vals[i<<1|1])+dels[i];
}
void psh(I i){
  for(I j=LOGN;j>=0;j--){
    I k=(i+FIXN)>>j;
    if(dels[k])app(k<<1,dels[k]),app(k<<1|1,dels[k]),dels[k]=0;
  }
}
void asn(I i,Lli val){
  vals[i+FIXN]=val;
}
void bld(){
  for(I i=FIXN-1;i>0;i--)vals[i]=max(vals[i<<1],vals[i<<1|1]);
}
void upd(I l,I r,Lli val){
  psh(l),psh(r-1);
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)app(i++,val);
    if(j&1)app(--j,val);
  }
  pll(l),pll(r-1);
}
Lli qry(I l,I r){
  psh(l),psh(r-1);
  Lli res=MIN;
  for(l+=FIXN,r+=FIXN;l<r;l>>=1,r>>=1){
    if(l&1)res=max(res,vals[l++]);
    if(r&1)res=max(res,vals[--r]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill_n(vals,2*FIXN,MIN);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)asn(i,a_arr[i]);
  bld();
  I m;cin>>m;
  while(m--){
    I t;cin>>t;
    if(t==1){
      I l,r,x;cin>>l>>r>>x,l--,r--;
      upd(l,r+1,x);
    }
    if(t==2){
      I l,r;cin>>l>>r,l--,r--;
      printf("%lli\n",qry(l,r+1));
    }
  }
}