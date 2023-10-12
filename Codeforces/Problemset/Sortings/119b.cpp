#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I N=100;
const Lf MIN=-1e9;
const Lf MAX=1e9;
I a_arr[N];
set<I>rems;
vector<I>trns;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)rems.insert(i);
  Lf low=MAX,upp=MIN;
  I q;cin>>q;
  while(q--){
    Lf ave=0;
    for(I i=0;i<n/k;i++){
      I t;cin>>t,t--;
      if(rems.find(t)!=rems.end())rems.erase(t);
      ave+=a_arr[t];
    }
    ave/=n/k;
    low=min(low,ave);
    upp=max(upp,ave);
  }
  if(rems.size()>n-n/k*k){
    for(auto t:rems)trns.push_back(a_arr[t]);
    sort(trns.begin(),trns.end());
    Lf ave1=0,ave2=0;
    for(I i=0;i<n/k;i++){
      ave1+=trns[i];
      ave2+=trns.end()[-1-i];
    }
    ave1/=n/k;
    ave2/=n/k;
    low=min(low,ave1);
    upp=max(upp,ave2);
  }
  printf("%.10Lf %.10Lf",low,upp);
}