#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=1000;
Lli a_arr[N];
vector<pair<Lli,Lli>>cpss;
multiset<Lli>unvs;
vector<Lli>tmps;
B inds[N*N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)if(i!=j)cpss.push_back({a_arr[i],a_arr[j]});
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(auto[x,y]:cpss){
    pair<Lli,Lli>tar={y,x+y};
    auto it=lower_bound(cpss.begin(),cpss.end(),tar);
    if(it!=cpss.end()&&*it==tar)inds[it-cpss.begin()]=1;
  }
  for(I i=0;i<n;i++)unvs.insert(a_arr[i]);
  I res=0;
  for(I i=0;i<cpss.size();i++)if(!inds[i]){
    auto[x,y]=cpss[i];
    tmps.clear();
    unvs.erase(unvs.find(x)),tmps.push_back(x);
    unvs.erase(unvs.find(y)),tmps.push_back(y);
    while(unvs.find(x+y)!=unvs.end())unvs.erase(unvs.find(x+y)),tmps.push_back(x+y),x+=y,swap(x,y);
    for(auto i:tmps)unvs.insert(i);
    res=max(res,(I)tmps.size());
  }
  I cnt=0;
  for(I i=0;i<n;i++)cnt+=a_arr[i]==0;
  printf("%i\n",max(res,cnt));
}