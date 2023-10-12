#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3000;
const Lli MOD=1e9+7;
I a_arr[N];
Lli pows[N+1];
vector<pair<I,Lli>>befs[N],afts[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<=N;i++)pows[i]=pows[i-1]*2%MOD;
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)for(I j=i+1;j<n;j++){
    I dis=a_arr[j]-a_arr[i];
    afts[i].push_back({dis,pows[n-1-j]});
    befs[j].push_back({dis,pows[i]});
  }
  for(I i=0;i<n;i++){
    sort(befs[i].begin(),befs[i].end());
    sort(afts[i].begin(),afts[i].end());
    for(I j=0;j+1<befs[i].size();j++)(befs[i][j+1].second+=befs[i][j].second)%=MOD;
    for(I j=0;j+1<afts[i].size();j++)(afts[i][j+1].second+=afts[i][j].second)%=MOD;
    sort(befs[i].begin(),befs[i].end());
    sort(afts[i].begin(),afts[i].end());
  }
  Lli res=(pows[n]-n-1+MOD)%MOD;
  for(I i=0;i<n;i++)for(I j=i+1;j<n;j++){
    I dis=a_arr[j]-a_arr[i];
    auto low=upper_bound(befs[i].begin(),befs[i].end(),pair<I,Lli>{dis,MOD});
    if(low==befs[i].begin())continue;
    auto upp=lower_bound(afts[j].begin(),afts[j].end(),pair<I,Lli>{dis,0});
    if(upp==afts[j].begin())continue;
    (res+=prev(low)->second*prev(upp)->second)%=MOD;
  }
  printf("%lli\n",res);
}
/*
for every adjacent pair of dots moving away from each other, there exists an
additional distinct coordinate where the dots stop

this means we can go through all pairs of dots and calculate their contribution
to the sum if they are moving away from each other
*/