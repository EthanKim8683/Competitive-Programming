#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=4e5;
const Lli MOD=1e9+7;

I a_arr[N];
I b_arr[N];
B viss[N];
vector<I>adjs[N];

void dfs(I a){
  if(viss[a])return;
  viss[a]=true;
  for(auto b:adjs[a])dfs(b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    fill_n(viss,n,false);
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)cin>>b_arr[i];
    for(I i=0;i<n;i++){
      I a=a_arr[i]-1,b=b_arr[i]-1;
      adjs[a].push_back(b);
      adjs[b].push_back(a);
    }
    Lli res=1;
    for(I i=0;i<n;i++){
      if(!viss[i])(res*=2)%=MOD;
      dfs(i);
    }
    printf("%lli\n",res);
  }
  return 0;
}