#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e6;
const Lli MOD=998244353;
I a_arr[N+1];
Lli pows[N+1];
Lli ps[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<=N;i++)pows[i]=pows[i-1]*2%MOD;
  I n;cin>>n;
  for(I i=1;i<=n;i++)cin>>a_arr[i];
  copy_n(a_arr,n+1,ps);
  for(I i=1;i+1<=n;i++)(ps[i+1]+=ps[i])%=MOD;
  Lli res=ps[n];
  for(I i=1;i<=n-1;i++)(res+=ps[i]*pows[n-1-i]%MOD*2)%=MOD;
  for(I i=1;i<=n-2;i++)(res+=ps[i]*pows[n-2-i]%MOD*(n-1-i))%=MOD;
  printf("%lli\n",res);
}
/*
for each length between rest stops, we can count the number of ways such a
stretch can exist (and thus, contribute)

for a stretch starting at Moscow and ending before Saratov, there is 1 position
and 2 ^ (n - 1 - i) distributions

for a stretch starting after Moscow and ending at Saratov, there is 1 position
and 2 ^ (n - 1 - i) distributions

for a stretch both starting at Moscow and ending at Saratov, there is 1
position and 1 distribution

for a stretch neither starting at Moscow nor ending at Saratov, there are
n - 1 - i positions and 2 ^ (n - 2 - i) distributions
*/