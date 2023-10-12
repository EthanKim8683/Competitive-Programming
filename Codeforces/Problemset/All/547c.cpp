#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2e5;
const I A=5e5;
I a_arr[N];
I eras[A+1];
I cnts[A+1];
B incs[N];
set<I>curs1;
vector<I>curs2;
vector<pair<I,I>>divs[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  iota(eras,eras+A+1,0);
  for(I i=2;i*i<=A;i++)for(I j=i*i;j<=A;j+=i)eras[j]=min(eras[j],i);
  I n,q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++){
    curs1.clear();
    for(I j=a_arr[i];j>1;j/=eras[j])curs1.insert(eras[j]);
    curs2.assign(curs1.begin(),curs1.end());
    for(I j=0;j<(1<<curs2.size());j++){
      I cur=1;
      for(I k=0;k<curs2.size();k++)if(j>>k&1)cur*=curs2[k];
      divs[i].push_back({cur,__builtin_popcount(j)%2==0?1:-1});
    }
  }
  Lli res=0;
  while(q--){
    I x;cin>>x,x--;
    if(incs[x]==1){
      for(auto[i,con]:divs[x])cnts[i]--,res-=cnts[i]*con;
      incs[x]=0;
    }else{
      for(auto[i,con]:divs[x])res+=cnts[i]*con,cnts[i]++;
      incs[x]=1;
    }
    printf("%lli\n",res);
  }
}
/*
we can represent each query as a contribution to the result, which is
positive or negative based on whether the beer isn't or is already on the
shelf, respectively

using the principle of inclusion-exclusion, it is possible to contribute only
beers that do not share a prime factor with the current beer

we can do this by prime factorizing each beer being queried and excluding
beers sharing 1 factor, include those sharing 2, exclude for 3, and so on
*/