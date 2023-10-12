#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
using B=bool;
const I N=500;
const I M=500;
const I MAX=1e9;
const Lli MOD=1e9+7;
B occs[N];
pair<I,Lli>dp[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    S s;cin>>s;
    S t;cin>>t;
    I n=s.size(),m=t.size();
    fill_n(occs,n,0);
    for(I i=0;i+m<=n;i++)occs[i]=s.substr(i,m)==t;
    fill_n(dp,n+1,pair<I,Lli>{MAX,0});
    dp[0]={0,1};
    auto cmb=[&](pair<I,Lli>&a,pair<I,Lli>b){
      if(b.first==a.first)(a.second+=b.second)%=MOD;
      if(b.first<a.first)a=b;
    };
    for(I i=0;i<n;i++){
      if(occs[i]){
        auto[cur,tot]=dp[i];
        for(I j=0;j<m;j++)if(occs[i+j])cmb(dp[i+j+m],{cur+1,tot});
      }else{
        cmb(dp[i+1],dp[i]);
      }
    }
    auto[cur,tot]=dp[n];
    printf("%i %lli\n",cur,tot);
  }
}
/*
we can use dynamic programming where, at the beginning of each occurrence, we
must transition at some point between the beginning and end of the occurrence,
but strictly at the beginning of some occurrence

each state will store both the minimum number of removals and the corresponding
number of ways

we don't need an extra dimension to handle the different number of removals
at each index because, if the number of removals is not minimal by some index,
it cannot be made minimal in remaining indices as the minimal number of
removals will be subject to the same number of (minimal) removals as the
former
*/