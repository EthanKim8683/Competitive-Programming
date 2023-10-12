#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100000;
const I L=10;
const Lli MOD=998244353;
I a_arr[N];
Lli pows[2*L+1];
I cnts[L+2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<=2*L;i++)pows[i]=pows[i-1]*10%MOD;
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++){
    I cnt=0;
    for(I j=a_arr[i];j;j/=10)cnt++;
    cnts[cnt]++;
  }
  Lli res=0;
  for(I i=0;i<n;i++){
    Lli pre=0;
    for(I j=a_arr[i],k=0;k<=L;j/=10,k++){
      Lli cur=(j*pows[2*k]+pre)%MOD;
      (res+=cur*cnts[k])%=MOD;
      (res+=10*cur*cnts[k+1])%=MOD;
      (pre+=j%10*pows[2*k])%=MOD;
    }
  }
  printf("%lli\n",res);
}
/*
similar to easy version, just accounting for each possible digit count
*/