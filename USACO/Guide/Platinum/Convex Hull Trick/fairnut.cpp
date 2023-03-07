#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e6;
const Lli LOGX=30;
const Lli FIXX=1ll<<LOGX;
const Lli MIN=-1e18;
tuple<Lli,Lli,Lli>rcts[N];
I chds[2*2*N+1][2];
pair<Lli,Lli>segs[2*2*N+1];
I t=1;
Lli exe(pair<Lli,Lli>fun,Lli x){
  auto[m,b]=fun;
  return m*x+b;
}
B cmp(pair<Lli,Lli>a,pair<Lli,Lli>b,Lli x){
  return exe(a,x)>exe(b,x);
}
void upd(pair<Lli,Lli>fun,Lli low=-FIXX,Lli upp=FIXX,I j=1){
  Lli mid=low+(upp-low)/2;
  B lcp=cmp(fun,segs[j],low),mcp=cmp(fun,segs[j],mid);
  if(mcp)swap(segs[j],fun);
  if(upp-low==1)return;
  lcp!=mcp?upd(fun,low,mid,chds[j][0]=chds[j][0]?:++t):upd(fun,mid,upp,chds[j][1]=chds[j][1]?:++t);
}
Lli qry(Lli x,Lli low=-FIXX,Lli upp=FIXX,I j=1){
  if(j==0)return MIN;
  if(upp-low==1)return exe(segs[j],x);
  Lli mid=low+(upp-low)/2;
  return max(exe(segs[j],x),x<mid?qry(x,low,mid,chds[j][0]):qry(x,mid,upp,chds[j][1]));
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    Lli x,y,a;cin>>x>>y>>a;
    rcts[i]={x,y,a};
  }
  sort(rcts,rcts+n);
  Lli res=MIN;
  for(I i=0;i<n;i++){
    auto[x,y,a]=rcts[i];
    Lli cur=x*y-a+qry(y);
    upd({-x,cur});
    res=max(res,cur);
  }
  printf("%lli\n",res);
}