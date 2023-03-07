#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
const I Q=1e5;
const I LOGN=30;
const I FIXN=1ll<<LOGN;
const I MIN=-1e9;
I chds[128*Q+1][2];
pair<I,I>vals[128*Q+1];
I dels[128*Q+1];
I t=1;
I n;
pair<I,I>cmb(pair<I,I>a,pair<I,I>b){
  auto[sum1,max1]=a;auto[sum2,max2]=b;
  return{sum1+sum2,max(max1,sum1+max2)};
}
void psh(I low,I upp,I j){
  if(upp-low>1&&dels[j]!=MIN){
    chds[j][0]=chds[j][0]?:++t,chds[j][1]=chds[j][1]?:++t;
    I tot=dels[j]*(upp-low)/2;
    vals[chds[j][0]]=vals[chds[j][1]]={tot,tot};
    dels[chds[j][0]]=dels[chds[j][1]]=dels[j];
    dels[j]=MIN;
  }
}
void pll(I low,I upp,I j){
  vals[j]=cmb(vals[chds[j][0]],vals[chds[j][1]]);
}
void upd(I l,I r,I val,I low=0,I upp=FIXN,I j=1){
  if(l>=upp||r<=low)return;
  if(l<=low&&r>=upp){
    I tot=val*(upp-low);
    vals[j]={tot,tot},dels[j]=val;
    return;
  }
  I mid=low+(upp-low)/2;
  psh(low,upp,j);
  upd(l,r,val,low,mid,chds[j][0]=chds[j][0]?:++t);
  upd(l,r,val,mid,upp,chds[j][1]=chds[j][1]?:++t);
  pll(low,upp,j);
}
pair<I,I>qry(I l,I r,I low=0,I upp=FIXN,I j=1){
  if(l>=upp||r<=low)return{0,0};
  if(l<=low&&r>=upp)return vals[j];
  I mid=low+(upp-low)/2;
  psh(low,upp,j);
  pair<I,I>res={0,0};
  res=cmb(res,qry(l,r,low,mid,chds[j][0]=chds[j][0]?:++t));
  res=cmb(res,qry(l,r,mid,upp,chds[j][1]=chds[j][1]?:++t));
  return res;
}
I fnd(I h){
  I l=0,r=n;
  while(l<r){
    I m=l+(r-l+1)/2;
    qry(1,m+1).second<=h?l=m:r=m-1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill_n(dels,128*Q+1,MIN);
  cin>>n;
  while(1){
    C t;cin>>t;
    if(t=='I'){
      I a,b,d;cin>>a>>b>>d;
      upd(a,b+1,d);
    }
    if(t=='Q'){
      I h;cin>>h;
      printf("%i\n",fnd(h));
    }
    if(t=='E'){
      break;
    }
  }
}