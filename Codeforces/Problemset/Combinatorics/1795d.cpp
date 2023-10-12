#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3e5;
const Lli MOD=998244353;
I w_arr[N];
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
  return facs[n]*inv(facs[k]*facs[n-k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>w_arr[i];
  Lli res=1;
  for(I i=0;i<n;i+=3){
    I upp=0;
    for(I j=0;j<3;j++)upp=max(upp,w_arr[i+j]+w_arr[i+(j+1)%3]);
    I cnt=0;
    for(I j=0;j<3;j++)cnt+=w_arr[i+j]+w_arr[i+(j+1)%3]==upp;
    (res*=cnt)%=MOD;
  }
  printf("%lli\n",res*bin(n/3,n/6)%MOD);
}
/*
each triple can be solved independently, since each contributes 2 vertices of
one color and 1 of another and coloring these groups equal amounts of either
pattern will always yield equal counts of red and blue

if we color a vertex a different color from the other two vertices in its
triple, all outgoing edges will be contributed
*/