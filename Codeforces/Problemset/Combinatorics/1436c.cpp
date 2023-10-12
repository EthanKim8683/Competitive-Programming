#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1000;
const Lli MOD=1e9+7;
Lli facs[N+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  if(n<0||k<0||n-k<0)return 0;
  return facs[n]*inv(facs[k]*facs[n-k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I n,x,pos;cin>>n>>x>>pos;
  I l=0,r=n,low=0,upp=0;
  while(l<r){
    I m=(l+r)/2;
    m==pos?l=m+1:m<pos?(low++,l=m+1):(upp++,r=m);
  }
  Lli res=1;
  (res*=bin(x-1,low))%=MOD;
  (res*=bin(n-x,upp))%=MOD;
  (res*=facs[low])%=MOD;
  (res*=facs[upp])%=MOD;
  (res*=facs[n-1-low-upp])%=MOD;
  printf("%lli\n",res);
}
/*
if middle < pos, a[middle] must be strictly less than x
if middle > pos, a[middle] must be strictly greater than x
if middle = pos, a[middle] must be equal to x

we can choose values less than or greater than x to fill these positions
*/