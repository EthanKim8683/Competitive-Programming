#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=1e6;
tuple<I,I,I>segs[2*N];
I n;
tuple<I,I,I>cmb(tuple<I,I,I>a,tuple<I,I,I>b){
  auto[a1,a2,a3]=a;
  auto[b1,b2,b3]=b;
  I cmb=min(a2,b3);
  return{a1+b1+2*cmb,a2+b2-cmb,a3+b3-cmb};
}
void upd(I i,tuple<I,I,I>x){
  for(segs[i+=n]=x;i>>=1;)segs[i]=cmb(segs[i<<1],segs[i<<1|1]);
}
tuple<I,I,I>qry(I l,I r){
  tuple<I,I,I>res1={0,0,0},res2={0,0,0};
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)res1=cmb(res1,segs[l++]);
    if(r&1)res2=cmb(segs[--r],res2);
  }
  return cmb(res1,res2);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  n=s.size();
  for(I i=0;i<n;i++){
    if(s[i]=='(')upd(i,{0,1,0});
    if(s[i]==')')upd(i,{0,0,1});
  }
  I m;cin>>m;
  while(m--){
    I l,r;cin>>l>>r;
    printf("%i\n",get<0>(qry(l-1,r)));
  }
}