#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e3;
const I M=1e3;
const I Q=1e5;
struct Seg{
  I val;
  Seg*l,*r;
  Seg(I val):val(val){}
  Seg(Seg*l,Seg*r):l(l),r(r){}
};
tuple<I,I,I>qrys[Q];
vector<Seg*>segs;
vector<B>invs;
I ress[Q+1];
I m;
I get(Seg*seg){
  return seg?seg->val:0;
}
Seg*bld(I l=0,I r=m){
  if(r-l==1)return new Seg(0);
  I m=l+(r-l)/2;
  Seg*seg=new Seg(bld(l,m),bld(m,r));
  seg->val=get(seg->l)+get(seg->r);
  return seg;
}
I qry(Seg*seg,I u,I v,I l=0,I r=m){
  if(u==l&&v==r)return seg->val;
  I m=l+(r-l)/2;
  if(v<=m)return qry(seg->l,u,v,l,m);
  if(u>=m)return qry(seg->r,u,v,m,r);
  return qry(seg->l,u,m,l,m)+qry(seg->r,m,v,m,r);
}
Seg*upd(Seg*seg,I i,I val,I l=0,I r=m){
  if(r-l==1)return new Seg(val);
  I m=l+(r-l)/2;
  if(i<m)seg=new Seg(upd(seg->l,i,val,l,m),seg->r);
  if(i>=m)seg=new Seg(seg->l,upd(seg->r,i,val,m,r));
  seg->val=get(seg->l)+get(seg->r);
  return seg;
}
I inv(I val,B inv){
  return inv?m-val:val;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>m>>q;
  for(I l=0;l<q;l++){
    I t;cin>>t;
    if(t==1){
      I i,j;cin>>i>>j,i--,j--;
      qrys[l]={1,i,j};
    }
    if(t==2){
      I i,j;cin>>i>>j,i--,j--;
      qrys[l]={2,i,j};
    }
    if(t==3){
      I i;cin>>i,i--;
      qrys[l]={3,i,-1};
    }
    if(t==4){
      I k;cin>>k;
      qrys[l]={4,k,-1};
    }
  }
  for(I i=0;i<n;i++){
    segs.clear(),invs.clear();
    segs.push_back(bld()),invs.push_back(0);
    I sum=0;
    for(I j=0;j<q;j++){
      auto[t,k,l]=qrys[j];
      sum-=inv(segs.back()->val,invs.back());
      if(t==1)segs.push_back(k==i?upd(segs.back(),l,invs.back()?0:1):segs.back()),invs.push_back(invs.back());
      if(t==2)segs.push_back(k==i?upd(segs.back(),l,invs.back()?1:0):segs.back()),invs.push_back(invs.back());
      if(t==3)segs.push_back(segs.back()),invs.push_back(k==i?!invs.back():invs.back());
      if(t==4)segs.push_back(segs[k]),invs.push_back(invs[k]);
      sum+=inv(segs.back()->val,invs.back());
      ress[j]+=sum;
    }
  }
  for(I i=0;i<q;i++)printf("%i\n",ress[i]);
}