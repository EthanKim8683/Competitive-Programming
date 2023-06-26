#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I K=2e5;
const I MAX=1e9+1;
pair<I,I>cars[N];
I g_arr[K];
vector<I>cofs;
vector<I>difs;
Lli ps[K+2];
Lli cnt(I v){
  I j=upper_bound(cofs.begin(),cofs.end(),v)-cofs.begin();
  return 3*(ps[difs.size()]-ps[j])-(Lli)(difs.size()-j)*v+ps[j]-ps[0];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k,s,t;cin>>n>>k>>s>>t;
  for(I i=0;i<n;i++){
    I c,v;cin>>c>>v;
    cars[i]={c,v};
  }
  for(I i=0;i<k;i++)cin>>g_arr[i];
  sort(g_arr,g_arr+k);
  for(I i=0;i+1<k;i++)difs.push_back(g_arr[i+1]-g_arr[i]);
  difs.push_back(g_arr[0]);
  difs.push_back(s-g_arr[k-1]);
  sort(difs.begin(),difs.end());
  for(auto i:difs)cofs.push_back(2*i);
  for(I i=0;i<difs.size();i++)ps[i+1]=ps[i]+difs[i];
  I res=MAX;
  for(I i=0;i<n;i++){
    auto[c,v]=cars[i];
    if(v<difs.back())continue;
    if(cnt(v)<=t)res=min(res,c);
  }
  printf("%i\n",res==MAX?-1:res);
}