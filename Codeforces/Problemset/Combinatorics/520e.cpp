#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using S=string;
const I N=1e5;
const Lli MOD=1e9+7;
Lli ps1[N+1];
Lli ps2[N+1];
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
  I n,k;cin>>n>>k;
  S s;cin>>s;
  for(I i=0;i<n;i++)ps1[i+1]=(ps1[i]*10+s[i]-'0')%MOD;
  for(I i=0;i<n;i++)ps2[i+1]=(ps2[i]+s[i]-'0')%MOD;
  auto rng1=[&](I l,I r){
    return(ps1[r]-ps1[l]*mpw(10,r-l))%MOD;
  };
  auto rng2=[&](I l,I r){
    return(ps2[r]-ps1[l])%MOD;
  };
  Lli res=0,cur=0;
  for(I i=1;i<=n-k;i++){
    (cur-=rng1(1,1+(i-1)))%=MOD;
    (cur+=mpw(10,i-1)*rng2(1,n-1-(i-1)))%=MOD;
    (res+=cur*bin((n-1)-(i-1)-2,k-2))%=MOD;
  }
  for(I i=1;i<=n-k;i++){
    Lli cur=(rng1(0,i)+rng1(n-i,n))%MOD;
    (res+=cur*bin((n-1)-(i-1)-1,k-1))%=MOD;
  }
  if(k==0)(res+=rng1(0,n))%=MOD;
  printf("%lli\n",(res+MOD)%MOD);
}
/*
we can find the sum among all j in [1, n - i - 1] the value represented by
substring [j, j + i) and multiply it with the number of ways to distribute
k - 2 pluses among (n - 1) - (i - 1) - 2 remaining in-betweens for all i in
[1, n - k]

to handle strings not bounded by pluses, we can find the the sum of the values
represented by [0, i) and [n - i, n) and multiply it with the number of ways
to distribute k - 1 pluses among (n - 1) - (i - 1) - 1 remaining in-betweens
for all i in [1, n - k]

if k is 0, then the entire string contributes to the sum

to find the sum among all j in [1, n - i - 1] the value represented by
substring [j, j + i) we can build on the sum of the previous i

effectively, we can "extend" each number in the previous set of numbers and
remove numbers which cannot be extended
*/