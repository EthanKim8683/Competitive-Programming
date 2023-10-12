#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I M=1e5;
const Lli MOD=1e9+7;
Lli facs[N+M+1];
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
  for(I i=1;i<=N+M;i++)facs[i]=facs[i-1]*i%MOD;
  I n,m,g;cin>>n>>m>>g;
  Lli res=m<=1;
  for(I i=1;i<=n;i++)(res=bin(i-1+m,m)-res)%=MOD;
  if(g==0)(res=bin(n+m,m)-res)%=MOD;
  printf("%lli\n",(res+MOD)%MOD);
}
/*
the number of ways g = 1 for n 0's and m 1's is the complement of the number
of ways g = 1 for n - 1 0's and m 1's (and so on), since there is only one
way to get g = 1 and that is for the previous modification to result in
another 0 and to pair a 0 with it

regarding the base case, m <= 1 will result in g = 1 when n = 0 since, if
m <= 1, g = 0 when n = 1
*/