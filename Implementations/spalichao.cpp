#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I Q=1e5;
const I LOGP=30;
const Lli FIXP=1ll<<LOGP;
const Lli MIN=-1e18;
I chds[2*Q+1][2];
pair<Lli,Lli>segs[2*Q+1];
I t=1;
Lli exe(pair<Lli,Lli>fun,Lli x){
  auto[m,b]=fun;
  return m*x+b;
}
B cmp(pair<Lli,Lli>a,pair<Lli,Lli>b,Lli x){
  return exe(a,x)>exe(b,x);
}
void upd(pair<Lli,Lli>fun,I j=1,Lli low=-FIXP,Lli upp=FIXP){
  Lli mid=low+(upp-low)/2;
  B lcp=cmp(fun,segs[j],low),mcp=cmp(fun,segs[j],mid);
  if(mcp)swap(segs[j],fun);
  if(upp-low==1)return;
  lcp!=mcp?upd(fun,chds[j][0]=chds[j][0]?:++t,low,mid):upd(fun,chds[j][1]=chds[j][1]?:++t,mid,upp);
}
Lli qry(Lli x,I j=1,Lli low=-FIXP,Lli upp=FIXP){
  if(j==0)return MIN;
  if(upp-low==1)return exe(segs[j],x);
  Lli mid=low+(upp-low)/2;
  Lli res=exe(segs[j],x);
  res=max(res,x<mid?qry(x,chds[j][0],low,mid):qry(x,chds[j][1],mid,upp));
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill_n(segs,2*Q+1,pair<Lli,Lli>{0,MIN});
  I q;cin>>q;
  while(q--){
    I t;cin>>t;
    if(t==1){
      I m,b;cin>>m>>b;
      upd({m,b});
    }
    if(t==2){
      I x;cin>>x;
      printf("%lli\n",qry(x));
    }
  }
}