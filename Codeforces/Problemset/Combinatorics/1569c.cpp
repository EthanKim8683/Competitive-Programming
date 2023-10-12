#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const Lli MOD=998244353;
Lli facs[N+1];
I a_arr[N];
map<I,I>cnts;
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
    for(I i=0;i<n;i++)cin>>a_arr[i];
    cnts.clear();
    for(I i=0;i<n;i++)cnts[a_arr[i]]++;
    auto[upp,cnt1]=*cnts.rbegin();
    if(cnt1>1){printf("%lli\n",facs[n]);continue;}
    I cnt2=cnts[upp-1];
    Lli res=0;
    for(I i=0;i<n;i++)(res+=(bin(n-1,cnt2)-bin(i,cnt2)*bin(n-1-i,0))%MOD*facs[cnt2]%MOD*facs[n-1-cnt2]%MOD)%=MOD;
    printf("%lli\n",(res+MOD)%MOD);
  }
}
/*
if the maximum value v of a appears at least twice, it is guaranteed the
condition is satisfied among all permutations

otherwise, as long as v - 1 appears at least once after v, the condition is
satisfied
*/