#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=20000;
const I LOGN=15;
const I FIXN=1<<LOGN;
const Lli MAX=1e18;
pair<I,I>tres[N];
pair<I,Lli>segs[2][2*FIXN];
Lli ps1[FIXN+1],ps2[FIXN+1],ps3[FIXN+1];
Lli exe(pair<I,Lli>fun,I x){
  auto[i,t]=fun;
  return ps1[x]-ps1[i]-ps2[i]*(ps3[x]-ps3[i])+t;
}
B cmp(pair<I,Lli>a,pair<I,Lli>b,I x){
  return exe(a,x)<exe(b,x);
}
void upd(pair<I,Lli>segs[],pair<I,Lli>fun){
  for(I i=0,l=0,r=FIXN,j=1;i<LOGN;i++){
    I m=l+(r-l)/2;
    B lcp=cmp(fun,segs[j],l),mcp=cmp(fun,segs[j],m);
    if(mcp)swap(fun,segs[j]);
    lcp!=mcp?(r=m,j=j<<1):(l=m,j=j<<1|1);
  }
}
Lli qry(pair<I,Lli>segs[],I x){
  Lli res=MAX;
  for(I i=x+FIXN;i>0;i>>=1)res=min(res,exe(segs[i],x));
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&segs[0][0],&segs[0][0]+2*2*FIXN,pair<I,Lli>{0,MAX});
  I n;cin>>n;
  if(n<=2)printf("0\n"),exit(0);
  for(I i=n-1;i>=0;i--){
    I w,d;cin>>w>>d;
    tres[i]={w,d};
  }
  for(I i=0;i<FIXN;i++){
    ps1[i+1]=ps1[i],ps2[i+1]=ps2[i],ps3[i+1]=ps3[i];
    if(i<n){
      auto[w,d]=tres[i];
      ps1[i+1]+=(ps2[i]+d)*w,ps2[i+1]+=d,ps3[i+1]+=w;
    }
  }
  for(I i=1;i<n;i++){
    upd(segs[0],{i,ps1[i-1]});
    upd(segs[1],{i,qry(segs[0],i-1)});
  }
  printf("%lli\n",qry(segs[1],n));
}