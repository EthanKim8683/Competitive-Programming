#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I LOGN=18;
const I FIXN=1<<LOGN;
I t_arr[N];
Lli vals[2*FIXN],dels1[2*FIXN],dels2[2*FIXN];
I siz(I i){
  return 1<<(__builtin_clz(i)-31+LOGN);
}
void app1(I i,Lli val){
  vals[i]+=val*siz(i);
  if(i<FIXN)dels2[i]?dels2[i]+=val,dels1[i]=0:dels1[i]+=val;
}
void app2(I i,Lli val){
  vals[i]=val*siz(i);
  if(i<FIXN)dels2[i]=val,dels1[i]=0;
}
void pll(I i){
  for(i+=FIXN;i>>=1;){
    vals[i]=vals[i<<1]+vals[i<<1|1];
    if(dels1[i])vals[i]+=dels1[i]*siz(i);
    if(dels2[i])vals[i]=dels2[i]*siz(i);
  }
}
void psh(I i){
  for(I j=LOGN;j>=0;j--){
    I k=(i+FIXN)>>j;
    if(dels1[k])app1(k<<1,dels1[k]),app1(k<<1|1,dels1[k]),dels1[k]=0;
    if(dels2[k])app2(k<<1,dels2[k]),app2(k<<1|1,dels2[k]),dels2[k]=0;
  }
}
void asn(I i,Lli val){
  vals[i+FIXN]=val;
}
void bld(){
  for(I i=FIXN-1;i>0;i--)vals[i]=vals[i<<1]+vals[i<<1|1];
}
void upd1(I l,I r,Lli val){
  psh(l),psh(r-1);
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)app1(i++,val);
    if(j&1)app1(--j,val);
  }
  pll(l),pll(r-1);
}
void upd2(I l,I r,Lli val){
  psh(l),psh(r-1);
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)app2(i++,val);
    if(j&1)app2(--j,val);
  }
  pll(l),pll(r-1);
}
Lli qry(I l,I r){
  psh(l),psh(r-1);
  Lli res=0;
  for(l+=FIXN,r+=FIXN;l<r;l>>=1,r>>=1){
    if(l&1)res+=vals[l++];
    if(r&1)res+=vals[--r];
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>t_arr[i];
  for(I i=0;i<n;i++)asn(i,t_arr[i]);
  bld();
  while(q--){
    I t;cin>>t;
    if(t==1){
      I a,b,x;cin>>a>>b>>x,a--,b--;
      upd1(a,b+1,x);
    }
    if(t==2){
      I a,b,x;cin>>a>>b>>x,a--,b--;
      upd2(a,b+1,x);
    }
    if(t==3){
      I a,b;cin>>a>>b,a--,b--;
      printf("%lli\n",qry(a,b+1));
    }
  }
}