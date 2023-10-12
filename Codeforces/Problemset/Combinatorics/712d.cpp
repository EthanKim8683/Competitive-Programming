#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I T=100;
const I K=1000;
const I A=100;
const I M=T*2*K;
Lli MOD=1e9+7;
Lli dp[T+1][2*M+1];
Lli ps[2*M+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I a,b,k,t;cin>>a>>b>>k>>t;
  dp[0][0+M]=1;
  for(I i=0;i<t;i++){
    I m1=i*2*k,m2=(i+1)*2*k;
    for(I j=-m2;j<=m2;j++)ps[j+M]=0;
    for(I j=-m1;j<=m1;j++){
      I l=j-2*k,m=j+1,r=j+2*k+2;
      (ps[l+M]+=dp[i][j+M])%=MOD;
      (ps[m+M]-=2*dp[i][j+M])%=MOD;
      (ps[r+M]+=dp[i][j+M])%=MOD;
    }
    for(I j=-m2;j+1<=m2;j++)(ps[j+1+M]+=ps[j+M])%=MOD;
    for(I j=-m2;j+1<=m2;j++)(ps[j+1+M]+=ps[j+M])%=MOD;
    for(I j=-m2;j<=m2;j++)(dp[i+1][j+M]+=ps[j+M])%=MOD;
  }
  Lli res=0;
  for(I i=b-a+1;i<=M;i++)(res+=dp[t][i+M])%=MOD;
  printf("%lli\n",(res+MOD)%MOD);
}
/*
if we center the problem around the difference between Memory and Lexa's
scores, we can say that Memory wins if his score increases by at least
b - a + 1

at each turn, Memory's score may vary by [-2 * k, 2 * k], where the number
of ways to get a variation i is min(i + 2 * k + 1, 2 * k + 1 - i)

we can use prefix sums to simulate this

using this, we can use dynamic programming to count the number of ways Memory
can have a strictly greater score than Lexa
*/