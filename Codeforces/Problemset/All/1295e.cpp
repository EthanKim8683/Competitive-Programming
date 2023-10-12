#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I LOGN=18;
const I FIXN=1<<LOGN;
const Lli MAX=1e18;
const Lli MIN=-MAX;
I p_arr[N];
I a_arr[N];
I invs[N];
Lli vals[2*FIXN];
Lli dels[2*FIXN];
void app(I i,Lli val){
  vals[i]+=val;
  if(i<FIXN)dels[i]+=val;
}
void psh(I i){
  for(I j=LOGN-1;j>0;j--){
    I k=(i+FIXN)>>j;
    app(k<<1,dels[k]),app(k<<1|1,dels[k]),dels[k]=0;
  }
}
void pll(I i){
  for(i+=FIXN;i>>=1;)vals[i]=min(vals[i<<1],vals[i<<1|1])+dels[i];
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
  Lli res=MAX;
  psh(l),psh(r-1);
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)res=min(res,vals[i++]);
    if(j&1)res=min(res,vals[--j]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I p;cin>>p,p--;
    invs[p]=i,p_arr[i]=p;
  }
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++){
    I j=invs[i];
    upd(j+1,FIXN,a_arr[j]);
  }
  Lli pre=0,res=MAX;
  for(I i=0;i<n;i++){
    I j=invs[i];
    pre+=a_arr[j],upd(j+1,FIXN,-2*a_arr[j]),res=min(res,pre+qry(1,n));
  }
  pre=0;
  for(I i=0;i<n-1;i++)pre+=a_arr[i],res=min(res,pre);
  pre=0;
  for(I i=n-1;i>0;i--)pre+=a_arr[i],res=min(res,pre);
  printf("%lli\n",res);
}
/*
initially sum of all a[i] such that p[i] less than value x, add minimum
prefix sum where -a[i] if a[i] less than or equal to x and a[i] if a greater
than x for each i

try for all x

can use a range update range query data structure to keep prefix sums and
query minimum for each x
*/