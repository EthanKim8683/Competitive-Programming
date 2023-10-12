#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=500000;
const Lli BAS=(1ll<<17)-1;
const Lli MOD=(1ll<<31)-1;
Lli c_arr[N];
Lli pows[N+1];
Lli hshs[N];
map<Lli,Lli>tots;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<=N;i++)pows[i]=pows[i-1]*BAS%MOD;
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>c_arr[i];
    fill_n(hshs,n,0);
    for(I i=0;i<m;i++){
      I u,v;cin>>u>>v,u--,v--;
      (hshs[v]+=pows[u])%=MOD;
    }
    tots.clear();
    for(I i=0;i<n;i++)tots[hshs[i]]+=c_arr[i];
    Lli res=0;
    for(auto[hsh,tot]:tots)if(hsh!=0)res=gcd(res,tot);
    printf("%lli\n",res);
  }
}
/*
knowing gcd(a, a + b) = gcd(a, b) and gcd(a, a - b) = gcd(a, b), we can
conclude that the combination of any two left-hand nodes x and y with
f({x}) = a, f({y}) = b and overlap f({x, y}) - a - b = c, results in
gcd(a, b, c):
  gcd(a, b, a + b - c)
= gcd(gcd(a, b), a + b - c)
= gcd(gcd(a, a + b), a + b - c)
= gcd(a, gcd(a + b, a + b - c))
= gcd(a, gcd(a + b, c))
= gcd(gcd(a, a + b), c)
= gcd(gcd(a, b), c)
= gcd(a, b, c)

this can be extended for any set of left-hand nodes by recursively combining
nodes in the set using this binary operation
*/