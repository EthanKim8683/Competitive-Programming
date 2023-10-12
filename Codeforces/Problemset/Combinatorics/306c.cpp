#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=4000;
const Lli MOD=1e9+9;
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
  I n,w,b;cin>>n>>w>>b;
  Lli res=0;
  for(I i=1;i<=min(b,n-2);i++)(res+=(n-i-1)*bin(b-i+i-1,i-1)%MOD*bin(w-(n-i)+(n-i)-1,(n-i)-1)%MOD*facs[b]%MOD*facs[w]%MOD)%=MOD;
  printf("%lli\n",res);
}
/*
we can count for all i the number of distributions of events for i bad days and
n - i good days

we can place the contiguous black stripe at any point in time in the next n
days as long as there is space for white stripes surrounding it, so there are
n - i - 1 placements of the black stripe

the number of ways to distribute x events among y days such that the order of
events matter (even within days) is the number of ways to distribute x
indistinguishable events among y days such that no day has less than one event,
multiplied by x! for all orders of events
*/