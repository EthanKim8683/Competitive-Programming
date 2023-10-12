#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const Lli MOD=998244353;
Lli facs[N+1];
Lli cnts[N+1];
Lli dp[N+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
I main(){
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I n,k;cin>>n>>k;
  for(I i=1;i<=k;i++)cnts[n-max(min(n-i,n),0)]++;
  Lli cur=1;
  for(I i=0;i<=n;i++)(cur*=mpw(i+1,cnts[i]))%=MOD;
  for(I i=0;i<=n;i++){
    dp[i]=cur;
    if(i==n)continue;
    (cur*=inv(mpw(n-i+1,cnts[n-i])))%=MOD;
    (cur*=inv(mpw(n-i,cnts[n-i-1])))%=MOD;
    cnts[n-i-1]+=cnts[n-i];
    (cur*=mpw(n-i,cnts[n-i-1]))%=MOD;
  }
  Lli pre=0,res=0;
  for(I i=n;i>=0;i--){
    (dp[i]-=pre)%=MOD,(pre+=dp[i])%=MOD;
    (res+=dp[i]*facs[n]%MOD*inv(facs[i])%MOD)%=MOD;
  }
  printf("%lli\n",(res+MOD)%MOD);
}
/*
for each set S[i] in an array, if we transform S[i] into T[i] by subtracting i
from each element, it becomes clear that S[i - 1] must be a subset of S[i]

thus, we can look at each element v in the final set T[n - 1] and count the
number of combinations of first occurrences of v in a set in the array

furthermore, since the order of the sets may be rearranged and each non-empty
S[i] is distinct, we can count the number of permutations of sets and account
for overcounting by dividing by the permutations of empty sets

we can maintain the number of number of possible first occurrences among each v
in [1, k] and truncate them each iteration
*/