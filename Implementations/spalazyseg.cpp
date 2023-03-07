#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I Q=1e5;
const I LOGP=30;
const Lli FIXP=1ll<<LOGP;
const Lli MIN=-1e18;
I chds[2*Q+1][2];
Lli vals[2*Q+1];
Lli dels[2*Q+1];
I t=1;
void psh(Lli low,Lli upp,I j){
  if(upp-low>1&&dels[j]){
    chds[j][0]=chds[j][0]?:++t,chds[j][1]=chds[j][1]?:++t;
    vals[chds[j][0]]+=dels[j],vals[chds[j][1]]+=dels[j];
    dels[chds[j][0]]+=dels[j],dels[chds[j][1]]+=dels[j];
    dels[j]=0;
  }
}
void pll(Lli low,Lli upp,I j){
  vals[j]=max(vals[chds[j][0]],vals[chds[j][1]]);
}
void upd(Lli l,Lli r,Lli val,Lli low=-FIXP,Lli upp=FIXP,I j=1){
  if(l>=upp||r<=low)return;
  if(l<=low&&r>=upp){vals[j]+=val,dels[j]+=val;return;}
  Lli mid=low+(upp-low)/2;
  psh(low,upp,j),upd(l,r,val,low,mid,chds[j][0]=chds[j][0]?:++t),upd(l,r,val,mid,upp,chds[j][1]=chds[j][1]?:++t),pll(low,upp,j);
}
Lli qry(Lli l,Lli r,Lli low=-FIXP,Lli upp=FIXP,I j=1){
  if(l>=upp||r<=low)return MIN;
  if(l<=low&&r>=upp)return vals[j];
  Lli mid=low+(upp-low)/2;
  psh(low,upp,j);
  return max(qry(l,r,low,mid,chds[j][0]=chds[j][0]?:++t),qry(l,r,mid,upp,chds[j][1]=chds[j][1]?:++t));
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    I t;cin>>t;
    if(t==1){
      Lli l,r,v;cin>>l>>r>>v;
      upd(l,r+1,v);
    }
    if(t==2){
      Lli l,r;cin>>l>>r;
      printf("%lli\n",qry(l,r+1));
    }
  }
}