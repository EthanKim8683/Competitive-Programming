#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e6+123;
const I M=1e6+123;
Lli ress[N];
Lli facs[M+1];
Lli mpw(Lli x,Lli y,Lli m){
  Lli res=1;
  for(x%=m;y;y>>=1,(x*=x)%=m)if(y&1)(res*=x)%=m;
  return res;
}
Lli inv(Lli x,Lli m){
  return mpw(x,m-2,m);
}
Lli bin(I n,I k,Lli m){
  if(n<0||k<0||n-k<0)return 0;
  return facs[n]*inv(facs[k]*facs[n-k],m)%m;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;Lli a,q;cin>>n>>m>>a>>q;
  Lli p=1;
  for(Lli t=a;t!=1;(t*=a)%=q,p++);
  facs[0]=1;
  for(I i=1;i<=max(n,m);i++)facs[i]=facs[i-1]*i%p;
  ress[0]=1;
  for(I i=1;i<n;i++)ress[i]=(ress[i-1]+bin(m,i,p))%p;
  for(I i=0;i<n;i++)printf("%lli ",mpw(a,ress[n-1-i],q));
}
/*
+ denotes element-wise addition

A[0] = [1, 1, 1, 1, 1, 1, 1, 1, 1, ...]
A[1] = [0, 1, 2, 3, 4, 5, 6, 7, 8, ...] + A[0]
A[2] = [0, 0, 1, 3, 6, 10, 15, 21, 28, ...] + A[0] + A[1]
A[3] = [0, 0, 0, 1, 4, 10, 20, 35, 56, ...] + A[0] + A[1] + A[2]
...
*/