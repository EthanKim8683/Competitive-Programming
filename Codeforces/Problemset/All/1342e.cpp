#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200000;
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
  return facs[n]*inv(facs[k]*facs[n-k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I n;Lli k;cin>>n>>k;
  Lli res=0;
  for(I i=0;i<=n-k-1;i++){
    Lli cur=1;
    (cur*=mpw(n-k-i,n))%=MOD;
    (cur*=bin(n-k,i))%=MOD;
    (cur*=bin(n,n-k))%=MOD;
    if(i%2==0)(res+=cur)%=MOD;
    if(i%2==1)(res-=cur)%=MOD;
  }
  if(n-k!=n)(res*=2)%=MOD;
  printf("%lli\n",(res+MOD)%MOD);
}
/*
if each empty cell is under attack and there are n rooks, there is either one
rook in each row or each column

we can group rooks by column if spread by row and row if spread by column,
making the number of attack pairs equal to n - m, where m is the number of
groups

now the problem can be simplified to finding the number of ways to split n
rooks into n - k non-empty groups along both axes (unless n - k = n), which
we can solve using the principle of inclusion-exclusion
*/