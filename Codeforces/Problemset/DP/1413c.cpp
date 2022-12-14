#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100000;
const I MAX=1e9;
I a_arr[6];
I b_arr[N];
I inds[N];
multiset<I>curs;
vector<pair<I,I>>vals;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  for(I i=0;i<6;i++)cin>>a_arr[i];
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>b_arr[i];
  sort(a_arr,a_arr+6,greater<I>());
  for(I i=0;i<n;i++)curs.insert(b_arr[i]-a_arr[inds[i]]);
  for(I i=0;i<n;i++)for(I j=0;j<6;j++)vals.push_back({b_arr[i]-a_arr[j],i});
  sort(vals.begin(),vals.end());
  I low=*curs.begin();
  I upp=*curs.rbegin();
  I res=upp-low;
  for(auto[val,i]:vals){
    curs.erase(curs.find(b_arr[i]-a_arr[inds[i]]));
    curs.insert(b_arr[i]-a_arr[min(++inds[i],5)]);
    I low=*curs.begin();
    I upp=*curs.rbegin();
    res=min(res,upp-low);
  }
  printf("%i\n",res);
}