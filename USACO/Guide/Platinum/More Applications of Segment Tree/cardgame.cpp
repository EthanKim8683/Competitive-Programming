#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=50000;
I elss[N];
B uses[2*N];
pair<I,I>segs1[2*2*N],segs2[2*2*N];
vector<I>bess;
I n;
pair<I,I>cmb1(pair<I,I>a,pair<I,I>b){
  auto[b1,e1]=a;auto[b2,e2]=b;
  return{b1+b2-min(b1,e2),e1+e2-min(b1,e2)};
}
pair<I,I>cmb2(pair<I,I>a,pair<I,I>b){
  auto[b1,e1]=a;auto[b2,e2]=b;
  return{b1+b2-min(e1,b2),e1+e2-min(e1,b2)};
}
void asn1(I i){
  segs1[i+2*n].first++;
}
void asn2(I i){
  segs1[i+2*n].second++;
}
void bld(){
  for(I i=2*n-1;i>0;i--)segs1[i]=cmb1(segs1[i<<1],segs1[i<<1|1]);
}
void upd1(I i){
  segs1[i+=2*n].first--,segs2[i].first++;
  for(I j=i;j>1;j>>=1)segs1[j>>1]=cmb1(segs1[j&~1],segs1[j|1]);
  for(I j=i;j>1;j>>=1)segs2[j>>1]=cmb2(segs2[j&~1],segs2[j|1]);
}
void upd2(I i){
  segs1[i+=2*n].second--,segs2[i].second++;
  for(I j=i;j>1;j>>=1)segs1[j>>1]=cmb1(segs1[j&~1],segs1[j|1]);
  for(I j=i;j>1;j>>=1)segs2[j>>1]=cmb2(segs2[j&~1],segs2[j|1]);
}
I qry1(I l=0,I r=2*n){
  pair<I,I>lrs={0,0},rrs={0,0};
  for(l+=2*n,r+=2*n;l<r;l>>=1,r>>=1){
    if(l&1)lrs=cmb1(lrs,segs1[l++]);
    if(r&1)rrs=cmb1(segs1[--r],rrs);
  }
  return cmb1(lrs,rrs).first;
}
I qry2(I l=0,I r=2*n){
  pair<I,I>lrs={0,0},rrs={0,0};
  for(l+=2*n,r+=2*n;l<r;l>>=1,r>>=1){
    if(l&1)lrs=cmb2(lrs,segs2[l++]);
    if(r&1)rrs=cmb2(segs2[--r],rrs);
  }
  return cmb2(lrs,rrs).first;
}
I main(){
#ifndef ETHANKIM8683
  freopen("cardgame.in","r",stdin);
  freopen("cardgame.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++){I els;cin>>els,elss[i]=els-1;}
  for(I i=0;i<n;i++)uses[elss[i]]=1;
  for(I i=0;i<2*n;i++)uses[i]?asn2(i):(asn1(i),bess.push_back(i));
  bld();
  sort(bess.begin(),bess.end(),greater<I>());
  I res=n-qry1()-qry2();
  for(I i=0;i<n;i++){
    upd1(bess[i]),upd2(elss[i]);
    res=max(res,n-qry1()-qry2());
  }
  printf("%i\n",res);
}