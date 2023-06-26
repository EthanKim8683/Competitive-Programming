#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3e5;
const I M=3e5;
I p_arr[N];
I inds[N];
pair<I,I>rngs[M];
vector<I>rgts[N];
multiset<I>rems;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>p_arr[i];
  for(I i=0;i<n;i++)inds[--p_arr[i]]=i;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a=inds[a-1],b=inds[b-1];
    if(a>b)swap(a,b);
    rngs[i]={a,b};
  }
  sort(rngs,rngs+m);
  for(I i=0;i<m;i++){
    auto[a,b]=rngs[i];
    rgts[a].push_back(b),rems.insert(b);
  }
  Lli res=0;
  for(I i=0;i<n;i++){
    auto it=rems.lower_bound(i);
    res+=(it==rems.end()?n:*it)-i;
    for(auto j:rgts[i])rems.erase(rems.find(j));
  }
  printf("%lli\n",res);
}