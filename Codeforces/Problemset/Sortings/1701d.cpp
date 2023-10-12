#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=5e5;
const I MAX=1e9;
I b_arr[N];
vector<pair<I,I>>adds[N+1];
set<pair<I,I>>rems;
I ress[N];
I n;
I fnd1(I i,I b){
  I l=1,r=n;
  while(l<r){
    I m=l+(r-l)/2;
    i/m<=b?r=m:l=m+1;
  }
  return l;
}
I fnd2(I i,I b){
  I l=1,r=n;
  while(l<r){
    I m=l+(r-l+1)/2;
    i/m>=b?l=m:r=m-1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)cin>>b_arr[i];
    for(I i=1;i<=n;i++)adds[i].clear();
    rems.clear();
    for(I i=0;i<n;i++){
      I b=b_arr[i];
      adds[fnd1(i+1,b)].push_back({fnd2(i+1,b),i});
    }
    for(I i=1;i<=n;i++){
      for(auto j:adds[i])rems.insert(j);
      auto it=rems.begin();
      ress[it->second]=i;
      rems.erase(it);
    }
    for(I i=0;i<n;i++)printf("%i ",ress[i]);
    printf("\n");
  }
}