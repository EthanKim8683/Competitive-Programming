#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I LOGN=18;
const I FIXN=1<<LOGN;
tuple<I,Lli,Lli>qrys[N];
vector<Lli>cpss;
Lli sizs[2*FIXN],vals[2*FIXN],dels1[2*FIXN],dels2[2*FIXN];
void app1(I i,I val){
  vals[i]=val*sizs[i];
  if(i<FIXN)dels1[i]=val,dels2[i]=0;
}
void app2(I i){
  vals[i]=sizs[i]-vals[i];
  if(i<FIXN)dels1[i]!=-1?dels1[i]=1-dels1[i],dels2[i]=0:dels2[i]^=1;
}
void dwn(I i){
  if(dels1[i]!=-1)app1(i<<1,dels1[i]),app1(i<<1|1,dels1[i]),dels1[i]=-1;
  if(dels2[i])app2(i<<1),app2(i<<1|1),dels2[i]=0;
}
void psh(I i){
  for(I j=LOGN-1;j>=0;j--)dwn((i+FIXN)>>j);
}
void pll(I i){
  for(i+=FIXN;i>>=1;){
    vals[i]=vals[i<<1]+vals[i<<1|1];
    if(dels1[i]!=-1)vals[i]=dels1[i]*sizs[i];
    if(dels2[i])vals[i]=sizs[i]-vals[i];
  }
}
void upd1(I l,I r,I val){
  psh(l),psh(r-1);
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)app1(i++,val);
    if(j&1)app1(--j,val);
  }
  pll(l),pll(r-1);
}
void upd2(I l,I r){
  psh(l),psh(r-1);
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)app2(i++);
    if(j&1)app2(--j);
  }
  pll(l),pll(r-1);
}
Lli qry(){
  dwn(1);
  if(vals[1]==sizs[1])return 1+sizs[1];
  Lli res=1;
  for(I i=1;i<FIXN;){
    i<<=1,dwn(i),dwn(i|1);
    if(vals[i]==sizs[i])res+=sizs[i],i|=1;
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I t;Lli l,r;cin>>t>>l>>r,r++;
    qrys[i]={t,l,r};
    cpss.push_back(l);
    cpss.push_back(r);
  }
  cpss.push_back(1);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<n;i++){
    auto[t,l,r]=qrys[i];
    l=lower_bound(cpss.begin(),cpss.end(),l)-cpss.begin();
    r=lower_bound(cpss.begin(),cpss.end(),r)-cpss.begin();
    qrys[i]={t,l,r};
  }
  for(I i=0;i+1<cpss.size();i++)sizs[i+FIXN]=cpss[i+1]-cpss[i];
  for(I i=FIXN-1;i>0;i--)sizs[i]=sizs[i<<1]+sizs[i<<1|1];
  fill_n(dels1,2*FIXN,-1);
  for(I i=0;i<n;i++){
    auto[t,l,r]=qrys[i];
    if(t==1)upd1(l,r,1);
    if(t==2)upd1(l,r,0);
    if(t==3)upd2(l,r);
    printf("%lli\n",qry());
  }
}
/*
we can compress the bounds and use range update range sum segment tree to
handle all queries

we can then walk on the segment tree, looking for the first missing segment
after each query
*/