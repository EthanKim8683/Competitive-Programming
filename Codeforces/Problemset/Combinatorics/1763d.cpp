#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100;
const Lli MOD=1e9+7;
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
    I n,i,j,x,y;cin>>n>>i>>j>>x>>y,i--,j--;
    if(x<y)swap(x,y),swap(i,j);
    Lli res=0;
    if(x==n){
      Lli cur=1;
      if(i<1||i>=n-1)cur=0;
      I p1=x-y-1,q1=abs(j-i)-1;
      (cur*=bin(p1,q1))%=MOD;
      I p2=y-1,q2;
      if(j<i){
        q2=j;
      }else{
        q2=n-1-j;
      }
      (cur*=bin(p2,q2))%=MOD;
      (res+=cur)%=MOD;
    }else{
      for(I k=1;k<n-1;k++){
        Lli cur=1;
        if(k==i||k==j)cur=0;
        I p1=n-x-1,q1=abs(i-k)-1;
        (cur*=bin(p1,q1))%=MOD;
        I p2=x-y-1,q2;
        if((j<k)==(i<k)){
          if(abs(j-k)<abs(i-k))cur=0;
          q2=abs(j-i)-1;
        }else{
          q2=abs(j-k)-(p1-q1)-1;
        }
        (cur*=bin(p2,q2))%=MOD;
        I p3=y-1,q3;
        if(j<k){
          q3=j;
        }else{
          q3=n-1-j;
        }
        (cur*=bin(p3,q3))%=MOD;
        (res+=cur)%=MOD;
      }
    }
    printf("%lli\n",res);
  }
}
/*
we can construct a bitonic permutation with peak k (B[k] = n) and pushing
elements to either the front or back of B from n - 1 to 1

to solve this problem for both B[i] = x and B[j] = y, assuming x > y and
x != n, we can for all k != i and k != j:

1. count the number of ways to distribute Pi = n - x - 1 pushes such that
   Qi = abs(i - k) - 1 of them are in the direction of i

2. count the number of ways to distribute Pj = x - y - 1 pushes such that:

   a. if i and j are in the same direction, Qj = abs(j - i) - 1 of them are in
      the direction of j

   b. if i and j are in opposite directions, Qj = abs(j - k) - (Pi - Qi) - 1 of
      them are in the direction of j

we may then distribute the remaining Pr = y - 1 pushes among Qr indices such
that:

1. if j < k, Qr = j

2. if j > k, Qr = n - 1 - j

if x = n, we must fix k = i and count the number of ways to distribute
Pj = x - y - 1 pushes such that Qj = abs(j - i) - 1 of them are in the
direction of j

the remaining Pr = y - 1 pushes can be distributed among Qr indices such that:

1. if j < i, Qr = j

2. if j > i, Qr = n - 1 - j
*/