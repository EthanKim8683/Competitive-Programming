#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=50;
const I M=1e5;
const Lli MOD=998244353;
pair<I,I>rngs[N];
Lli dp1[N+1][M+1];
Lli dp2[M+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r;
    rngs[i]={l,r};
  }
  for(I i=1;i<=m;i++){
    for(I j=0;j<=n;j++)for(I k=0;k<=m/i;k++)dp1[j][k]=0;
    dp1[0][0]=1;
    for(I j=0;j<n;j++){
      for(I k=0;k<=m/i;k++){
        auto[l,r]=rngs[j];
        l=(l+i-1)/i,r=r/i+1;
        if(k+l<=m/i)(dp1[j+1][k+l]+=dp1[j][k])%=MOD;
        if(k+r<=m/i)(dp1[j+1][k+r]-=dp1[j][k])%=MOD;
      }
      for(I k=0;k+1<=m/i;k++)(dp1[j+1][k+1]+=dp1[j+1][k])%=MOD;
    }
    for(I j=0;j<=m/i;j++)(dp2[i]+=dp1[n][j])%=MOD;
  }
  for(I i=m;i>=1;i--)for(I j=2*i;j<=m;j+=i)(dp2[i]-=dp2[j])%=MOD;
  printf("%lli\n",(dp2[1]+MOD)%MOD);
}
/*
for each x in [1, m], we can count the number of arrays such that the gcd sum
is a multiple of x

this can be done using dynamic programming by index and y, where x * y is the
array sum (this is to ensure the complexity with regards to m is O(m * ln(m)))

furthermore, we can transition using prefix sums

finally, we can use principle of inclusion-exclusion to count the number of
arrays such that the gcd sum is exactly x (by subtracting the number of arrays
that are multiples of x)
*/