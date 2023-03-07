#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I LOGN=17;
const I FIXN=1<<LOGN;
const I MIN=-1e9;
pair<I,I>segs[2*FIXN];
I exe(pair<I,I>fun,I x){
  auto[m,b]=fun;
  return m*x+b;
}
B cmp(pair<I,I>a,pair<I,I>b,I x){
  return exe(a,x)>exe(b,x);
}
void upd(pair<I,I>fun){
  for(I i=0,l=0,r=FIXN,j=1;i<LOGN;i++){
    I m=l+(r-l)/2;
    B lcp=cmp(fun,segs[j],l),mcp=cmp(fun,segs[j],m);
    if(mcp)swap(fun,segs[j]);
    lcp!=mcp?(r=m,j=j<<1):(l=m,j=j<<1|1);
  }
}
I qry(I x){
  I res=MIN;
  for(I i=x+FIXN;i>0;i>>=1)res=max(res,exe(segs[i],x));
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill_n(segs,2*FIXN,pair<I,I>{0,MIN});
  I q;cin>>q;
  while(q--){
    I t;cin>>t;
    if(t==1){
      I m,b;cin>>m>>b;
      upd({m,b});
    }
    if(t==2){
      I x;cin>>x;
      printf("%i\n",qry(x));
    }
  }
}