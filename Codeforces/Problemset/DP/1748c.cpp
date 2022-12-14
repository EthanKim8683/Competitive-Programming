#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

I a_arr[N];
Lli ps[N];
vector<I>inds;
map<Lli,I>pres[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)ps[i]=a_arr[i];
    for(I i=0;i+1<n;i++)ps[i+1]+=ps[i];
    for(I i=0;i<n;i++)pres[i].clear();
    inds.clear();
    for(I i=0;i<n;i++)if(a_arr[i]==0)inds.push_back(i);
    I res=0;
    for(I i=0;i<n;i++){
      auto it=upper_bound(inds.begin(),inds.end(),i);
      if(it==inds.begin()){res+=ps[i]==0;continue;}
      I j=*--it;
      pres[j][ps[i]]++;
    }
    for(I i=0;i<n;i++){
      I cur=0;
      for(auto[pre,cnt]:pres[i])cur=max(cur,cnt);
      res+=cur;
    }
    printf("%i\n",res);
  }
}