#include<iostream>
#include<cstdio>
#include<vector>
#include<tuple>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;

/*
Process array in reverse, solving queries by
beginning as we go. Their ends can be queried
for using binary search since the stack is
monotonic.
*/

const I N=2e5;
const I Q=2e5;
const I MAX=1e9+1;

I x_arr[N];
vector<pair<I,I>> qrys[N];
vector<tuple<I,I,I,Lli>>stks;
Lli ps[N+1];
Lli ress[Q];

auto fnd(I i){
  return upper_bound(stks.begin(),stks.end(),tuple<I,I,I,Lli>{i,MAX,MAX,MAX},greater<tuple<I,I,I,Lli>>());
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  for(I i=0;i<n;i++)
    ps[i+1]=ps[i]+x_arr[i];
  for(I i=0;i<q;i++){
    I a,b;cin>>a>>b;
    a--,b--;
    qrys[a].push_back({b+1,i});
    ress[i]-=ps[b+1]-ps[a];
  }
  stks.push_back({n,n,MAX,0});
  for(I i=n-1;i>=0;i--){
    I x=x_arr[i];
    while(get<2>(stks.back())<=x)stks.pop_back();
    auto[j,k,y,acc]=stks.back();
    acc+=(Lli)y*(k-j);
    Lli sum=acc+(Lli)x*(j-i);
    stks.push_back({i,j,x,acc});
    for(auto[j,ind]:qrys[i]){
      auto[k,l,x,acc]=*fnd(j);
      ress[ind]+=sum-((Lli)x*(l-j)+acc);
    }
  }
  for(I i=0;i<q;i++)printf("%lli\n",ress[i]);
  return 0;
}