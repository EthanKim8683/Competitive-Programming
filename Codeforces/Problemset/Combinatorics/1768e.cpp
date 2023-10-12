#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e6;
Lli facs[3*N+1];
Lli m;
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=m;y;y>>=1,(x*=x)%=m)if(y&1)(res*=x)%=m;
  return res;
}
Lli inv(Lli x){
  return mpw(x,m-2);
}
Lli bin(I n,I k){
  return facs[n]*inv(facs[k]*facs[n-k])%m;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>m;
  facs[0]=1;
  for(I i=1;i<=3*n;i++)facs[i]=facs[i-1]*i%m;
  Lli res=0;
  for(I i=1;i<=n;i++)(res+=bin(n,i)*bin(n,i)%m*bin(2*n,n-i)%m*facs[i]%m*facs[n-i]%m*facs[2*n]%m)%=m;
  (res+=facs[3*n]-facs[2*n])%=m;
  for(I i=1;i<=n;i++)(res+=bin(n,i)*bin(n,i)%m*bin(2*n,n-i)%m*facs[i]%m*facs[n-i]%m*facs[2*n]%m)%=m;
  (res+=facs[2*n]-1)%=m;
  printf("%lli\n",(res+m)%m);
}
/*
since any permutation can be sorted in increasing order using the minimum
number of operations via some subsequence of sorting [0, 2 * n), sorting
[n, 3 * n), then sorting [0, 2 * n) again, we can calculate the contribution
of each element of the sequence among all permutations

conditions for sorting [0, 2 * n) (1):
- if [0, n) originally contains any [2 * n, 3 * n)

invariants before sorting [n, 3 * n):
- all [2 * n, 3 * n) is only contained in [n, 3 * n)

conditions for sorting [n, 3 * n):
- if [2 * n, 3 * n) is originally incomplete

invariants before sorting [0, 2 * n) (2):
- [2 * n, 3 * n) is complete

conditions for sorting [0, 2 * n) (2):
- if [0, n) originally contains any [2 * n, 3 * n):
  - if [2 * n, 3 * n) originally contains any [0, n)
- if [0, n) does not originally contain any [2 * n, 3 * n):
  - if [0, n) is originally incomplete
*/