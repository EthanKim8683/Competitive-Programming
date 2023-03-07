#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using Lli=long long int;
const I N=100000;
const Lli MAX=1e18;
pair<I,I>locs[N];
Lli segs1[2*(N-1)];
Lli segs2[2*(N-2)];
I n;
void asn1(I i,Lli x){
  segs1[i+n-1]=x;
}
void asn2(I i,Lli x){
  segs2[i+n-2]=x;
}
void bld1(){
  for(I i=n-2;i>0;i--)segs1[i]=segs1[i<<1]+segs1[i<<1|1];
}
void bld2(){
  for(I i=n-3;i>0;i--)segs2[i]=min(segs2[i<<1],segs2[i<<1|1]);
}
void upd1(I i,Lli x){
  for(segs1[i+=n-1]=x;i>1;i>>=1)segs1[i>>1]=segs1[i]+segs1[i^1];
}
void upd2(I i,Lli x){
  for(segs2[i+=n-2]=x;i>1;i>>=1)segs2[i>>1]=min(segs2[i],segs2[i^1]);
}
Lli qry1(I l,I r){
  Lli res=0;
  for(l+=n-1,r+=n-1;l<r;l>>=1,r>>=1){
    if(l&1)res+=segs1[l++];
    if(r&1)res+=segs1[--r];
  }
  return res;
}
Lli qry2(I l,I r){
  Lli res=MAX;
  for(l+=n-2,r+=n-2;l<r;l>>=1,r>>=1){
    if(l&1)res=min(res,segs2[l++]);
    if(r&1)res=min(res,segs2[--r]);
  }
  return res;
}
Lli val1(I i){
  auto[x1,y1]=locs[i];auto[x2,y2]=locs[i+1];
  return abs(x1-x2)+abs(y1-y2);
}
Lli val2(I i){
  auto[x1,y1]=locs[i];auto[x2,y2]=locs[i+2];
  return abs(x1-x2)+abs(y1-y2)-(val1(i)+val1(i+1));
}
I main(){
#ifndef ETHANKIM8683
  freopen("marathon.in","r",stdin);
  freopen("marathon.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>n>>q;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    locs[i]={x,y};
  }
  for(I i=0;i+1<n;i++)asn1(i,val1(i));
  for(I i=0;i+2<n;i++)asn2(i,val2(i));
  bld1(),bld2();
  while(q--){
    C t;cin>>t;
    if(t=='U'){
      I i,x,y;cin>>i>>x>>y,i--;
      locs[i]={x,y};
      if(i-1>=0)upd1(i-1,val1(i-1));
      if(i+1<n)upd1(i,val1(i));
      if(i-2>=0)upd2(i-2,val2(i-2));
      if(i-1>=0)upd2(i-1,val2(i-1));
      if(i+2<n)upd2(i,val2(i));
    }
    if(t=='Q'){
      I i,j;cin>>i>>j,i--,j--;
      if(i==j)printf("0\n");
      else if(i+1==j)printf("%lli\n",val1(i));
      else printf("%lli\n",qry1(i,j)+qry2(i,j-1));
    }
  }
}