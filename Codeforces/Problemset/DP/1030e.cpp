#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=3e5;
const I LOGA=60;
const I MIN=-1e9;
Lli a_arr[N];
I pops[N];
I ps[N+2];
vector<I>stks;
vector<I>pres[2];
B cmp(I a,I b){
  return ps[a]<ps[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)pops[i]=__builtin_popcountll(a_arr[i]);
  for(I i=0;i<n;i++)ps[i+1]=ps[i]+pops[i];
  Lli res=0;
  stks.push_back(MIN);
  for(I i=0;i<n;i++){
    pres[ps[i]%2].push_back(i);
    while(stks.size()>1&&pops[stks.back()]<=pops[i])stks.pop_back();
    stks.push_back(i);
    for(I j=1;j<stks.size();j++){
      I l=stks[j-1],r=stks[j],pop=pops[r],k=ps[i+1]%2;
      auto low=upper_bound(pres[k].begin(),pres[k].end(),l);
      auto upp=upper_bound(pres[k].begin(),pres[k].end(),r);
      ps[n+1]=ps[i+1]-2*pop;
      res+=upper_bound(low,upp,n+1,cmp)-low;
    }
  }
  printf("%lli\n",res);
}