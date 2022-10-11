#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

I b_arr[N];
vector<I>adjs[N+2];
vector<I>ress;

B cmp(I a,I b){
  return adjs[a].size()<adjs[b].size();
}

void dfs(I a){
  sort(adjs[a].begin(),adjs[a].end(),cmp);
  ress.push_back(a);
  for(auto b:adjs[a])dfs(b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    ress.clear();
    for(I i=0;i<=n+1;i++)adjs[i].clear();
    for(I i=0;i<n;i++)cin>>b_arr[i];
    I k=b_arr[0]?n:0;
    for(I i=1;i<n;i++)if(b_arr[i-1]>i&&b_arr[i]<=i)k=i;
    for(I i=0;i<n;i++)adjs[b_arr[i]].push_back(i+1);
    dfs(0),dfs(n+1);
    printf("%i\n",k);
    for(auto i:ress)if(i!=0&&i!=n+1)printf("%i ",i);
    printf("\n");
  }
}