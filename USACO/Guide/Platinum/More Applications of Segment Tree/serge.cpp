#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=300000;
const I M=300000;
const I A=1e6;
I a_arr[N];
I b_arr[M];
pair<I,I>vals[A+1];
pair<I,I>segs[2*(A+1)];
pair<I,I>cmb(pair<I,I>a,pair<I,I>b){
  auto[la,lb]=a;auto[ra,rb]=b;
  I d=min(la,rb);la-=d,rb-=d;
  return{la+ra,lb+rb};
}
pair<I,I>fix(pair<I,I>x){
  auto[a,b]=x;
  return{a-min(a,b),b-min(a,b)};
}
void asn(I i,pair<I,I>x){
  segs[i+A+1]=fix(x);
}
void bld(){
  for(I i=A;i>0;i--)segs[i]=cmb(segs[i<<1],segs[i<<1|1]);
}
void upd(I i,pair<I,I>x){
  for(segs[i+=A+1]=fix(x);i>1;i>>=1)segs[i>>1]=cmb(segs[i&~1],segs[i|1]);
}
pair<I,I>qry(I l,I r){
  pair<I,I>lrs={0,0},rrs={0,0};
  for(l+=A+1,r+=A+1;l<r;l>>=1,r>>=1){
    if(l&1)lrs=cmb(lrs,segs[l++]);
    if(r&1)rrs=cmb(segs[--r],rrs);
  }
  return cmb(lrs,rrs);
}
B chk(I x){
  return qry(x,A+1).first;
}
I fnd(){
  I l=-1,r=A;
  while(l<r){
    I m=l+(r-l+1)/2;
    chk(m)?l=m:r=m-1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<m;i++)cin>>b_arr[i];
  for(I i=0;i<n;i++)vals[a_arr[i]].first++;
  for(I i=0;i<m;i++)vals[b_arr[i]].second++;
  for(I i=1;i<=A;i++)asn(i,vals[i]);
  bld();
  I q;cin>>q;
  while(q--){
    I t;cin>>t;
    if(t==1){
      I i,x;cin>>i>>x,i--;
      vals[a_arr[i]].first--;
      upd(a_arr[i],vals[a_arr[i]]);
      a_arr[i]=x;
      vals[a_arr[i]].first++;
      upd(a_arr[i],vals[a_arr[i]]);
    }
    if(t==2){
      I i,x;cin>>i>>x,i--;
      vals[b_arr[i]].second--;
      upd(b_arr[i],vals[b_arr[i]]);
      b_arr[i]=x;
      vals[b_arr[i]].second++;
      upd(b_arr[i],vals[b_arr[i]]);
    }
    I res=fnd();
    printf("%i\n",res);
  }
}