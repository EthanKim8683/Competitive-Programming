#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2000;
const Lli MOD=1e9+7;
I a_arr[N];
Lli tris[N];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k,k--;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++){
    Lli tri=1;
    for(I j=1;j<=i;j++)(tri*=k+j)%=MOD,(tri*=inv(j))%=MOD;
    tris[i]=tri;
  }
  for(I i=0;i<n;i++){
    Lli res=a_arr[i];
    for(I j=0;j<i;j++)(res+=tris[i-j]*a_arr[j])%=MOD;
    printf("%lli ",res);
  }
}
/*
we can calculate the contribution of each element to each index

the contribution of the element i to index j is the (j - i)-dimensional
triangle sum of elements [1, k]
*/