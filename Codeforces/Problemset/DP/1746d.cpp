#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
vector<I>adjs[N];
I s_arr[N];
Lli vals[N];
vector<Lli>rems[N];
Lli res=0;
Lli dfs(I a,Lli val){
  vals[a]=val;
  Lli div=adjs[a].size();
  if(!div)return s_arr[a];
  Lli quo=val/div,rem=val%div;
  for(auto b:adjs[a])rems[a].push_back(dfs(b,quo));
  sort(rems[a].begin(),rems[a].end(),greater<Lli>());
  for(int i=0;i<rem;i++)res+=rems[a][i];
  return s_arr[a]+rems[a][rem];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)rems[i].clear(),adjs[i].clear();
    for(I i=1;i<n;i++){I p;cin>>p,adjs[p-1].push_back(i);}
    for(I i=0;i<n;i++)cin>>s_arr[i];
    res=0,dfs(0,k);
    for(I i=0;i<n;i++)res+=s_arr[i]*vals[i];
    printf("%lli\n",res);
  }
}