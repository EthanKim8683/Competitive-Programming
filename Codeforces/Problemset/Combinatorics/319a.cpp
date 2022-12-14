#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const Lli MOD=1e9+7;
const I N=100;
Lli pows[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  pows[0]=1;
  for(I i=1;i<=n;i++)pows[i]=pows[i-1]*2%MOD;
  Lli res=0;
  for(I i=0;i<n;i++){
    if(s[i]=='0')continue;
    Lli cur=1;
    (cur*=pows[i])%=MOD;
    (cur*=pows[n-i-1])%=MOD;
    (cur*=pows[n-i-1])%=MOD;
    (res+=cur)%=MOD;
  }
  printf("%lli\n",res);
}