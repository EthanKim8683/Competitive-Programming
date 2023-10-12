#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const Lli MOD=1e9+7;
I eras[N+1];
I cops[N+1];
set<I>prms1;
vector<I>prms2;
map<I,I>cnts1;
vector<pair<I,I>>cnts2;
Lli res=0;
void dfs(Lli val,Lli sum,Lli gcd=1,I i=0){
  if(i==cnts2.size()){
    (res+=lcm(val,gcd)*cops[sum/gcd])%=MOD;
    return;
  }
  auto[prm,cnt]=cnts2[i];
  for(I j=0;j<=cnt;j++)dfs(val,sum,gcd,i+1),gcd*=prm;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  iota(eras,eras+N+1,0);
  for(I i=2;i*i<=N;i++)for(I j=i*i;j<=N;j+=i)eras[j]=min(eras[j],i);
  I n;cin>>n;
  for(I i=2;i<=n;i++){
    prms1.clear();
    for(I j=i;j>1;j/=eras[j])prms1.insert(eras[j]);
    prms2.assign(prms1.begin(),prms1.end());
    for(I j=0;j<(1<<prms2.size());j++){
      I cur=__builtin_popcount(j)&1?-1:1;
      for(I k=0;k<prms2.size();k++)if(j>>k&1)cur*=prms2[k];
      cops[i]+=i/cur;
    }
  }
  for(I i=1;i<=n-2;i++){
    cnts1.clear();
    for(I j=n-i;j>1;j/=eras[j])cnts1[eras[j]]++;
    cnts2.assign(cnts1.begin(),cnts1.end());
    dfs(i,n-i);
  }
  printf("%lli\n",res);
}
/*
for each gcd(a, b) (call it g) to exist, a + b must divisible by g, and the
resulting quotient must be representable as a sum of two coprime integers

for any a and x such that a + b = x for some b, if a is divisible by a prime
factor of x, b must be as well, meaning the number of coprime pairs a and b
must be equal to the number of numbers [1, x] not divisible by any prime
factor of x, which can be found using the principle of inclusion-exclusion

this means that we can go through all c, try all divisors g of n - c, and sum
the number of coprime sum representations of (n - c) / g multiplied by
lcm(c, g) for each c
*/