#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=1e5;
const Lli MOD=998244353;
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
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S s;cin>>s;
    I cnt1=0,cnt2=0;
    for(I i=0;i+1<n;i++)if(s[i]=='1'&&s[i+1]=='1')cnt1++,i++;
    for(I i=0;i<n;i++)if(s[i]=='0')cnt2++;
    printf("%lli\n",bin(cnt2+cnt1,cnt1));
  }
}
/*
each "double" is capable of moving to any position, even passing through
1's

therefore, the number of states reachable is equal to the number of ways to
choose positions for all doubles
*/