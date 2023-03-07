#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I Q=1e5;
const I LOGP=30;
const Lli FIXP=1ll<<LOGP;
I chds[2*Q+1][2];
Lli segs[2*Q+1];
I t=1;
void upd(Lli i,Lli val,Lli low=-FIXP,Lli upp=FIXP,I j=1){
  if(upp-low==1){segs[j]+=val;return;}
  Lli mid=low+(upp-low)/2;
  i<mid?upd(i,val,low,mid,chds[j][0]=chds[j][0]?:++t):upd(i,val,mid,upp,chds[j][1]=chds[j][1]?:++t);
  segs[j]=segs[chds[j][0]]+segs[chds[j][1]];
}
Lli qry(Lli l,Lli r,Lli low=-FIXP,Lli upp=FIXP,I j=1){
  if(l>=upp||r<=low||j==0)return 0;
  if(l<=low&&r>=upp)return segs[j];
  Lli mid=low+(upp-low)/2;
  return qry(l,r,low,mid,chds[j][0])+qry(l,r,mid,upp,chds[j][1]);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    I t;cin>>t;
    if(t==1){
      Lli p,v;cin>>p>>v;
      upd(p,v);
    }
    if(t==2){
      Lli l,r;cin>>l>>r;
      printf("%lli\n",qry(l,r+1));
    }
  }
}