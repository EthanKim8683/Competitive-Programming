#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;
const I K=100;
const Lli MOD=1e9+7;

I pars[N];

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

I siz(I i){
  return -pars[fnd(i)];
}

Lli pow(Lli x,I y){
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
  I n,k;cin>>n>>k;
  fill_n(pars,n,-1);
  for(I i=0;i<n-1;i++){
    I u,v,x;cin>>u>>v>>x,u--,v--;
    if(x==0)uni(u,v);
  }
  Lli res=pow(n,k);
  for(I i=0;i<n;i++)if(fnd(i)==i)
    (res-=pow(siz(i),k))%=MOD;
  printf("%lli\n",(res+MOD)%MOD);
  return 0;
}