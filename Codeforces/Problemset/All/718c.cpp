#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100000;
const I LOGN=17;
const I FIXN=1<<LOGN;
const I LOGX=47;
const Lli MOD=1e9+7;
I a_arr[N];
pair<Lli,Lli>fibs[LOGX+1];
pair<Lli,Lli>vals[2*FIXN];
Lli dels[2*FIXN];
pair<Lli,Lli>add(pair<Lli,Lli>a,pair<Lli,Lli>b){
  auto[x,y]=a;auto[z,w]=b;
  return{(x+z)%MOD,(y+w)%MOD};
}
pair<Lli,Lli>get(pair<Lli,Lli>fib,Lli i){
  for(I j=LOGX;j>=0;j--)if(i>>j&1){
    auto[a,b]=fib;auto[c,d]=fibs[j];
    Lli e=(c+d)%MOD;
    fib={((b-a)*c+a*d)%MOD,((b-a)*d+a*e)%MOD};
    i^=1ll<<j;
  }
  return fib;
}
void app(I i,Lli val){
  vals[i]=get(vals[i],val);
  if(i<FIXN)dels[i]+=val;
}
void psh(I i){
  for(I j=LOGN-1;j>0;j--){
    I k=(i+FIXN)>>j;
    if(dels[k])app(k<<1,dels[k]),app(k<<1|1,dels[k]),dels[k]=0;
  }
}
void pll(I i){
  for(i+=FIXN;i>>=1;){
    vals[i]=add(vals[i<<1],vals[i<<1|1]);
    if(dels[i])vals[i]=get(vals[i],dels[i]);
  }
}
void asn(I i,pair<Lli,Lli>val){
  vals[i+FIXN]=val;
}
void bld(){
  for(I i=FIXN-1;i>0;i--)vals[i]=add(vals[i<<1],vals[i<<1|1]);
}
void upd(I l,I r,Lli val){
  psh(l),psh(r-1);
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)app(i++,val);
    if(j&1)app(--j,val);
  }
  pll(l),pll(r-1);
}
Lli qry(I l,I r){
  psh(l),psh(r-1);
  Lli res=0;
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)(res+=vals[i++].first)%=MOD;
    if(j&1)(res+=vals[--j].first)%=MOD;
  }
  return(res+MOD)%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  pair<Lli,Lli>fib={1,1};
  for(I i=0;i<=LOGX;i++){
    fibs[i]=fib;
    auto[a,b]=fib;
    Lli c=(a+b)%MOD;
    fib={((b-a)*a+a*b)%MOD,((b-a)*b+a*c)%MOD};
  }
  for(I i=0;i<n;i++)asn(i,get({0,1},a_arr[i]));
  bld();
  for(I i=0;i<m;i++){
    I t;cin>>t;
    if(t==1){
      I l,r,x;cin>>l>>r>>x,l--;
      upd(l,r,x);
    }
    if(t==2){
      I l,r;cin>>l>>r,l--;
      printf("%lli\n",qry(l,r));
    }
  }
}
/*
just looking at the first three terms of a fibonacci sequence, (0, 1, 1), we
can construct the basis of fibonacci-like sequences through a linear
combination of (0, 1) and (1, 1)

this means that for coefficients a and b and basis (x, y) such that
a * (0, 1) + b * (1, 1) = (x, y), the nth fibonacci-like number will equal
a * fib(n) + b * fib(n + 1)

this allows us to use a binary lifting approach to answer fibonacci queries
in O(log2(X))

the range updates and range queries can then be handled using lazy segment
tree
*/