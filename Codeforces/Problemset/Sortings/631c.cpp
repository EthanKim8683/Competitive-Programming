#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=200000;
I a_arr[N];
vector<pair<I,I>>stks;
multiset<I>rems;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<m;i++){
    I t,r;cin>>t>>r;
    while(stks.size()&&stks.back().second<=r)stks.pop_back();
    stks.push_back({t,r});
  }
  reverse(stks.begin(),stks.end());
  I k=stks.back().second,ord;
  for(I i=0;i<k;i++)rems.insert(a_arr[i]);
  for(I i=k-1;i>=0;i--){
    if(stks.size()&&i<stks.back().second){
      ord=stks.back().first;
      stks.pop_back();
    }
    if(ord==1)a_arr[i]=*rems.rbegin();
    if(ord==2)a_arr[i]=*rems.begin();
    rems.erase(rems.find(a_arr[i]));
  }
  for(I i=0;i<n;i++)printf("%i ",a_arr[i]);
}