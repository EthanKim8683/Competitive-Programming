#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const Lli MOD=998244353;
I a_arr[N];
set<I>curs1;
vector<I>curs2;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    Lli res=1;
    for(I i=1;i<n;i++){
      I a=a_arr[i],g=a_arr[i-1];
      if(a==g){(res*=m/a)%=MOD;continue;}
      if(gcd(g,a)!=a){res=0;break;}
      I f=g/a;
      curs1.clear();
      for(I j=2;j*j<=f;j++)for(;f%j==0;f/=j)curs1.insert(j);
      if(f>1)curs1.insert(f);
      curs2.assign(curs1.begin(),curs1.end());
      I con=0;
      for(I j=0;j<(1<<curs2.size());j++){
        I cur=a;
        for(I k=0;k<curs2.size();k++)if(j>>k&1)cur*=curs2[k];
        con+=(__builtin_popcount(j)%2?-1:1)*(m/cur);
      }
      (res*=con)%=MOD;
    }
    printf("%lli\n",res);
  }
}
/*
each b[i] can be solved independently as it only depends on g = gcd(b[0], b[1],
b[2], ..., b[i - 1])

to find the number of ways to produce a[i] from gcd(g, b[i]), we must look at
the prime factorization of g and a[i]

if g contains the same amount of a prime p as a[i], b[i] can contain any power
of p no less than said amount

if g contains fewer of prime p than a[i], gcd(g, b[i]) can never equal a[i]

if g contains more of prime p than a[i], b[i] must contain the exact same
amount of prime p as a[i]

we can find the number of b[i] satisfying each prime using the principle of
inclusion-exclusion, which, if we do only when g != a[i], ensures happens
at most log(N) times, since bitmasking is expensive
*/