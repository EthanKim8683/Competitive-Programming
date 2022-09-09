#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2000;
const Lli MOD=1e9+7;

I pars[N];
I cnt;

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
  cnt--;
}

Lli pow(Lli x,Lli y){
  x%=MOD;
  Lli res=1;
  while(y){
    if(y&1)(res*=x)%=MOD;
    (x*=x)%=MOD;
    y>>=1;
  }
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  fill_n(pars,n,-1);
  cnt=n;
  for(I i=0;i+k-1<n;i++){
    I l=i,r=i+k-1;
    while(l<r)uni(l++,r--);
  }
  printf("%lli\n",pow(m,cnt));
  return 0;
}