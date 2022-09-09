#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=2e5;
const I MAX=1e9;

I c_arr[N];
I a_arr[N];
I deps[N];
B viss[N];
vector<I>cycs;
I dep=0;

I dfs1(I a){
  if(deps[a]!=-1)return deps[a];
  deps[a]=dep++;
  I res=dfs1(a_arr[a]);
  dep--;
  deps[a]=MAX;
  if(res<=dep)cycs.push_back(a);
  return res;
}

void dfs2(I a){
  if(viss[a])return;
  viss[a]=1;
  dfs2(a_arr[a]);
}

B cmp(I a,I b){
  return c_arr[a]<c_arr[b];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(deps,n,-1);
  for(I i=0;i<n;i++)cin>>c_arr[i];
  for(I i=0;i<n;i++){I a;cin>>a,a_arr[i]=a-1;}
  for(I i=0;i<n;i++)dfs1(i);
  sort(cycs.begin(),cycs.end(),cmp);
  Lli res=0;
  for(auto i:cycs)if(!viss[i])
    dfs2(i),res+=c_arr[i];
  printf("%lli\n",res);
  return 0;
}