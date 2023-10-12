#include<bits/stdc++.h>
using namespace std;
using I=int;
const I P=1e6;
const I Q=1e9;
I facs[P+1];
set<I>prms1;
vector<I>prms2;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  iota(facs,facs+P+1,0);
  for(I i=2;i*i<=P;i++)for(I j=i*i;j<=P;j+=i)facs[j]=facs[i];
  I t;cin>>t;
  while(t--){
    I x,p,k;cin>>x>>p>>k;
    prms1.clear();
    for(I t=p;t>1;t/=facs[t])prms1.insert(facs[t]);
    prms2.assign(prms1.begin(),prms1.end());
    auto cnt=[&](I q){
      I res=0;
      for(I i=0;i<(1<<prms2.size());i++){
        I cur=1;
        for(I j=0;j<prms2.size();j++)if(i>>j&1)cur*=prms2[j];
        res+=(__builtin_popcount(i)%2==0?1:-1)*(q/cur);
      }
      return res;
    };
    I pre=cnt(x),l=x+1,r=Q;
    while(l<r){
      I m=l+(r-l)/2;
      cnt(m)-pre>=k?r=m:l=m+1;
    }
    printf("%lli\n",l);
  }
}
/*
we can use the principle of inclusion-exclusion to find the number of integers
y such that gcd(p, y) = 1 where y <= q

using binary search we can find the minimum integer q such that the number of
such integers no greater than q is k
*/