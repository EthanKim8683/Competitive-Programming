#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I P=1000000;
const Lli MOD=1e9+7;
I pars[P];
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
  return-pars[fnd(i)];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I p,k;cin>>p>>k;
  if(k==0){
    Lli res=1;
    for(I i=1;i<p;i++)(res*=p)%=MOD;
    printf("%lli\n",res),exit(0);
  }
  if(k==1){
    Lli res=1;
    for(I i=0;i<p;i++)(res*=p)%=MOD;
    printf("%lli\n",res),exit(0);
  }
  fill_n(pars,p,-1);
  for(I i=0;i<p;i++)uni(i,(Lli)k*i%p);
  Lli res=1;
  for(I i=0;i<p;i++)if(fnd(i)==i&&siz(i)>1)(res*=p)%=MOD;
  printf("%lli\n",res);
}
/*
since f(k * x % p) = k * f(x) % p, we can say that f(x) is dependent on
f(k * x % p) (f(x) = f(k * x % p) * inv(k) % p) and vice versa

this means that we can represent the problem as a functional graph, where
one node x's f(x) can determine every other node X's f(X)

therefore, the number of distinct f that satisfy the equation is equal
to p ^ m, where m is the number of connected components of size greater than 1
*/