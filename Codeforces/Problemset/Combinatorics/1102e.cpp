#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const Lli MOD=998244353;
const I MAX=1e9;
I a_arr[N];
I pars[N];
map<I,I>rots;
I vals[N];
I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}
void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}
void cmb(I&a,I b){
  a=min(a,b);
}
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  fill_n(vals,n,MAX);
  fill_n(pars,n,-1);
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(!rots.count(a))rots[a]=i;
    uni(rots[a],i);
  }
  vals[fnd(0)]=0;
  for(I i=0;i+1<n;i++)cmb(vals[fnd(i+1)],vals[fnd(i)]+1);
  printf("%lli\n",mpw(2,vals[fnd(n-1)]));
}