#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const Lli MOD=1e9+7;
Lli facs[N+1];
I a_arr[N];
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
    I sum=a_arr[0];
    for(I i=1;i<n;i++)sum&=a_arr[i];
    for(I i=0;i<n;i++)a_arr[i]^=sum;
    I cnt=0;
    for(I i=0;i<n;i++)cnt+=a_arr[i]==0;
    printf("%lli\n",2*bin(cnt,2)*facs[n-2]%MOD);
  }
}
/*
for a permutation to be good, all prefixes must equal a[0], all suffixes must
equal a[n - 1] and a[0] must equal a[n - 1]

this is because, if we process each i from left to right, the left half can't
gain bits and the right half can't lose bits, so the only way for the halves
to be equal is for all prefixes and suffixes to be equal

if we take the and-sum k of array a, we can xor each a[i] with k

now, we just need to fix 0's at the beginning and end of the sequence

this is because, since we "xor out" the and-sum, there always exists a prefix
or suffix with and-sum 0, meaning a[0] and a[n - 1] must be 0 to begin with
*/