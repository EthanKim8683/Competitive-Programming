#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I MIN=-1e9;
Lli c_arr[N];
Lli t_arr[N];
set<pair<Lli,I>>upps;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>c_arr[i];
  for(I i=0;i<n;i++)cin>>t_arr[i];
  if(c_arr[0]!=t_arr[0])printf("No\n"),exit(0);
  for(I i=1;i<n;i++)upps.insert({c_arr[i]-c_arr[i-1],i});
  for(I i=1;i<n;i++){
    auto it=upps.lower_bound({t_arr[i]-t_arr[i-1],MIN});
    if(it==upps.end())printf("No\n"),exit(0);
    if(it->first!=t_arr[i]-t_arr[i-1])printf("No\n"),exit(0);
    upps.erase(it);
  }
  printf("Yes\n");
}