#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=200000;
const I LOGN=18;
const I FIXN=1<<LOGN;
const Lli MAX=1e18;
I a_arr[N];
Lli vals[2*FIXN],dels[2*FIXN];
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
void asn(I i,Lli val){
  vals[i+FIXN]=val;
}
void bld(){
  for(I i=FIXN-1;i>0;i--)vals[i]=min(vals[i<<1],vals[i<<1|1]);
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
  Lli res=MAX;
  for(l+=FIXN,r+=FIXN;l<r;l>>=1,r>>=1){
    if(l&1)res=min(res,vals[l++]);
    if(r&1)res=min(res,vals[--r]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  fill_n(vals,2*FIXN,MAX);
  for(I i=0;i<n;i++)asn(i,a_arr[i]);
  bld();
  I m;cin>>m,cin.ignore();
  while(m--){
    S lin;getline(cin,lin);
    istringstream sin(lin);
    I l,r,v;sin>>l>>r;
    if(sin>>v){
      if(r<l)upd(l,n,v),upd(0,r+1,v);
      if(r>=l)upd(l,r+1,v);
    }else{
      if(r<l)printf("%lli\n",min(qry(l,n),qry(0,r+1)));
      if(r>=l)printf("%lli\n",qry(l,r+1));
    }
  }
}