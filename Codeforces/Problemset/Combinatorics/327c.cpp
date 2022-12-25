#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=1e5;
const Lli MOD=1e9+7;
I n;
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli mfl(Lli x){
  Lli res=0;
  for(Lli y=1,z=mpw(2,n);x;x>>=1,(y*=1+z)%=MOD,(z*=z)%=MOD)if(x&1)(res*=z)%=MOD,(res+=y)%=MOD;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S a;cin>>a;
  I k;cin>>k;
  n=a.size();
  Lli cnt=0;
  for(I i=0;i<n;i++)if(a[i]=='0'||a[i]=='5')(cnt+=mpw(2,i))%=MOD;
  printf("%lli\n",mfl(k)*cnt%MOD);
}