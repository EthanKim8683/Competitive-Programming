#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=200000;
const I MIN=-1e9;
const I MAX=1e9;
pair<I,I>crds[N];
tuple<B,B,B,B,I,I,I,I>segs[2*N];
I n;
tuple<B,B,B,B,I,I,I,I>cmb(tuple<B,B,B,B,I,I,I,I>a,tuple<B,B,B,B,I,I,I,I>b){
  auto[xx1,xy1,yx1,yy1,lx1,ly1,rx1,ry1]=a;auto[xx2,xy2,yx2,yy2,lx2,ly2,rx2,ry2]=b;
  B xx3=0,xy3=0,yx3=0,yy3=0;
  if(rx1<=lx2)xx3|=xx1&xx2,xy3|=xx1&xy2,yx3|=yx1&xx2,yy3|=yx1&xy2;
  if(rx1<=ly2)xx3|=xx1&yx2,xy3|=xx1&yy2,yx3|=yx1&yx2,yy3|=yx1&yy2;
  if(ry1<=lx2)xx3|=xy1&xx2,xy3|=xy1&xy2,yx3|=yy1&xx2,yy3|=yy1&xy2;
  if(ry1<=ly2)xx3|=xy1&yx2,xy3|=xy1&yy2,yx3|=yy1&yx2,yy3|=yy1&yy2;
  return{xx3,xy3,yx3,yy3,lx1,ly1,rx2,ry2};
}
void asn(I i,pair<I,I>v){
  auto[x,y]=v;
  segs[i+n]={1,0,0,1,x,y,x,y};
}
void bld(){
  for(I i=n-1;i>0;i--)segs[i]=cmb(segs[i<<1],segs[i<<1|1]);
}
void upd(I i,pair<I,I>v){
  auto[x,y]=v;
  for(segs[i+=n]={1,0,0,1,x,y,x,y};i>1;i>>=1)segs[i>>1]=cmb(segs[i&~1],segs[i|1]);
}
B qry(I l,I r){
  tuple<B,B,B,B,I,I,I,I>lrs={1,1,1,1,MIN,MIN,MIN,MIN},rrs={1,1,1,1,MAX,MAX,MAX,MAX};
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)lrs=cmb(lrs,segs[l++]);
    if(r&1)rrs=cmb(segs[--r],rrs);
  }
  auto[xx,xy,yx,yy,lx,ly,rx,ry]=cmb(lrs,rrs);
  return xx|xy|yx|yy;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    crds[i]={x,y};
  }
  for(I i=0;i<n;i++)asn(i,crds[i]);
  bld();
  I m;cin>>m;
  while(m--){
    I a,b;cin>>a>>b,a--,b--;
    swap(crds[a],crds[b]),upd(a,crds[a]),upd(b,crds[b]);
    printf("%s\n",qry(0,n)?"TAK":"NIE");
  }
}