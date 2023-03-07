#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I Q=1e5;
const I LOGP=30;
const Lli FIXP=1ll<<LOGP;
I chds[2*LOGP*Q+1][2];
Lli vals[2*LOGP*Q+1];
B dels[2*LOGP*Q+1];
I t=1;
void psh(Lli low,Lli upp,I j){
  if(upp-low>1){
    chds[j][0]=chds[j][0]?:++t,chds[j][1]=chds[j][1]?:++t;
    if(dels[j])vals[chds[j][0]]=vals[chds[j][1]]=(upp-low)/2;
    dels[chds[j][0]]|=dels[j],dels[chds[j][1]]|=dels[j];
  }
  dels[j]=0;
}
void pll(Lli low,Lli upp,I j){
  vals[j]=vals[chds[j][0]]+vals[chds[j][1]];
}
void upd(Lli l,Lli r,Lli low=0,Lli upp=FIXP,I j=1){
  if(l>=upp||r<=low)return;
  if(l<=low&&r>=upp){vals[j]=upp-low,dels[j]=1;return;}
  Lli mid=low+(upp-low)/2;
  psh(low,upp,j);
  upd(l,r,low,mid,chds[j][0]=chds[j][0]?:++t);
  upd(l,r,mid,upp,chds[j][1]=chds[j][1]?:++t);
  pll(low,upp,j);
}
Lli qry(Lli l,Lli r,Lli low=0,Lli upp=FIXP,I j=1){
  if(l>=upp||r<=low)return 0;
  if(l<=low&&r>=upp)return vals[j];
  Lli mid=low+(upp-low)/2;
  psh(low,upp,j);
  Lli res=0;
  res+=qry(l,r,low,mid,chds[j][0]=chds[j][0]?:++t);
  res+=qry(l,r,mid,upp,chds[j][1]=chds[j][1]?:++t);
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>m;
  Lli c=0;
  while(m--){
    I d;cin>>d;
    if(d==1){
      Lli x,y;cin>>x>>y;
      c=qry(x+c,y+c+1);
      printf("%lli\n",c);
    }
    if(d==2){
      Lli x,y;cin>>x>>y;
      upd(x+c,y+c+1);
    }
  }
}