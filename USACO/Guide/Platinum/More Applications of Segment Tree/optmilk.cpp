#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=40000;
const Lli MIN=-1e18;
I m_arr[N];
tuple<Lli,Lli,Lli,Lli>segs[2*N];
I n;
tuple<Lli,Lli,Lli,Lli>cmb(tuple<Lli,Lli,Lli,Lli>a,tuple<Lli,Lli,Lli,Lli>b){
  auto[nn1,ny1,yn1,yy1]=a;auto[nn2,ny2,yn2,yy2]=b;
  Lli nn3=max(nn1+nn2,max(ny1+nn2,nn1+yn2));
  Lli ny3=max(nn1+ny2,max(ny1+ny2,nn1+yy2));
  Lli yn3=max(yn1+nn2,max(yy1+nn2,yn1+yn2));
  Lli yy3=max(yn1+ny2,max(yy1+ny2,yn1+yy2));
  return{nn3,ny3,yn3,yy3};
}
void asn(I i,Lli x){
  segs[i+n]={0,MIN,MIN,x};
}
void bld(){
  for(I i=n-1;i>0;i--)segs[i]=cmb(segs[i<<1],segs[i<<1|1]);
}
void upd(I i,Lli x){
  for(segs[i+=n]={0,MIN,MIN,x};i>1;i>>=1)segs[i>>1]=cmb(segs[i&~1],segs[i|1]);
}
Lli qry(I l,I r){
  tuple<Lli,Lli,Lli,Lli>lrs={0,0,0,0},rrs={0,0,0,0};
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)lrs=cmb(lrs,segs[l++]);
    if(r&1)rrs=cmb(segs[--r],rrs);
  }
  auto[nn,ny,yn,yy]=cmb(lrs,rrs);
  return max(nn,max(ny,max(yn,yy)));
}
I main(){
#ifndef ETHANKIM8683
  freopen("optmilk.in","r",stdin);
  freopen("optmilk.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I d;cin>>n>>d;
  for(I i=0;i<n;i++)cin>>m_arr[i];
  for(I i=0;i<n;i++)asn(i,m_arr[i]);
  bld();
  Lli res=0;
  while(d--){
    I i,m;cin>>i>>m,i--;
    upd(i,m);
    res+=qry(0,n);
  }
  printf("%lli\n",res);
}