#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=5000;
Lli facs[N+1];
Lli p;
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=p;y;y>>=1,(x*=x)%=p)if(y&1)(res*=x)%=p;
  return res;
}
Lli inv(Lli x){
  return mpw(x,p-2);
}
Lli bin(I n,I k){
  return facs[n]*inv(facs[k]*facs[n-k])%p;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>p;
  facs[0]=1;
  for(I i=1;i<=n;i++)facs[i]=facs[i-1]*i%p;
  Lli res=0;
  for(I i=n/2;i<=n-2;i++)for(I j=0;j<=n-i-2;j++){
    Lli cur=1;
    (cur*=bin(n-i-2,j))%=p;
    (cur*=facs[i+j-1])%=p;
    (cur*=n/2*2-i)%=p;
    (res+=cur)%=p;
  }
  if(n%2==0)(res+=facs[n-1-1])%=p;
  (res*=n)%=p;
  printf("%lli\n",res);
}