#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e6;
const I LOGN=20;
const I FIXN=1<<LOGN;
const I MAX=1e9;
const Lli MIN=-1e18;
pair<I,I>segs[4*FIXN];
vector<I>cpss;
Lli dp[N];
Lli a,b,c;
I exp(I i){
  if(i>=cpss.size())return cpss.back()+i;
  return cpss[i];
}
I cps(I x){
  return lower_bound(cpss.begin(),cpss.end(),x)-cpss.begin();
}
Lli exe(pair<I,I>fun,Lli x){
  auto[d,i]=fun;
  if(d==MAX)return MIN;
  return a*(x-=d)*x+b*x+c+dp[i];
}
B cmp(pair<I,I>a,pair<I,I>b,Lli x){
  return exe(a,x)>exe(b,x);
}
void upd(pair<I,I>fun){
  for(I i=0,l=0,r=FIXN,j=1;i<LOGN;i++){
    I m=l+(r-l)/2;
    B lcp=cmp(fun,segs[j],exp(l)),mcp=cmp(fun,segs[j],exp(m));
    if(mcp)swap(fun,segs[j]);
    lcp!=mcp?(r=m,j=j<<1):(l=m,j=j<<1|1);
  }
}
Lli qry(I x){
  Lli res=MIN;
  for(I i=cps(x)+FIXN;i>0;i>>=1)res=max(res,exe(segs[i],x));
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill_n(segs,4*FIXN,pair<I,I>{MAX,0});
  I n;cin>>n;
  cin>>a>>b>>c;
  I cur=0;
  for(I i=0;i<n;i++){
    I x;cin>>x;
    cpss.push_back(cur+=x);
  }
  for(I i=0;i<n;i++){
    I x=cpss[i];
    dp[i]=max(a*x*x+b*x+c,qry(x));
    upd({x,i});
  }
  printf("%lli\n",dp[n-1]);
}