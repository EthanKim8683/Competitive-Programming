#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
const I N=500000;
C fans[N+1];
tuple<I,I,I,I,I>segs[2*N];
I n;
tuple<I,I,I,I,I>cmb(tuple<I,I,I,I,I>a,tuple<I,I,I,I,I>b){
  auto[ic1,it1,dc1,dt1,o1]=a;auto[ic2,it2,dc2,dt2,o2]=b;
  I di=min(ic1,it2);ic1-=di,it2-=di;
  I dt=min(dt1,dc2);dt1-=dt,dc2-=dt;
  I ic3=ic1+ic2,it3=it1+it2;
  I dc3=dc1+dc2,dt3=dt1+dt2;
  o1=min(o1,dt1),o2=min(o2,it2);
  I o3=o1+o2+min(dt1-o1,it2-o2);
  return{ic3,it3,dc3,dt3,o3};
}
void asn1(I i){
  get<0>(segs[i+n])++,get<2>(segs[i+n])++;
}
void asn2(I i){
  get<1>(segs[i+n])++,get<3>(segs[i+n])++,get<4>(segs[i+n])++;
}
void bld(){
  for(I i=n-1;i>0;i--)segs[i]=cmb(segs[i<<1],segs[i<<1|1]);
}
I qry(I l,I r){
  tuple<I,I,I,I,I>lrs={0,0,0,0,0},rrs={0,0,0,0,0};
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)lrs=cmb(lrs,segs[l++]);
    if(r&1)rrs=cmb(segs[--r],rrs);
  }
  auto[ic,it,dc,dt,o]=cmb(lrs,rrs);
  return it+dt-o;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  cin>>fans;
  for(I i=0;i<n;i++)fans[i]=='C'?asn1(i):asn2(i);
  bld();
  I q;cin>>q;
  while(q--){
    I l,r;cin>>l>>r,l--,r--;
    printf("%i\n",qry(l,r+1));
  }
}