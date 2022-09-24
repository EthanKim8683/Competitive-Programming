#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=2e5;

Lli a_arr[N];
I b_arr[N];
B viss[N];
vector<I>tops;
vector<I>adjs[N];

void dfs1(I a){
  if(viss[a])return;
  viss[a]=1;
  I b=b_arr[a];
  if(b!=-1)dfs1(b-1);
  tops.push_back(a);
}

void dfs2(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto b:adjs[a])dfs2(b);
  tops.push_back(a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>b_arr[i];
  for(I i=0;i<n;i++)dfs1(i);
  reverse(tops.begin(),tops.end());
  Lli res=0;
  for(auto i:tops){
    I j=b_arr[i];
    Lli a=a_arr[i];
    res+=a;
    if(j==-1)continue;
    j--;
    if(a>=0)adjs[i].push_back(j),a_arr[j]+=a;
    else adjs[j].push_back(i);
  }
  fill_n(viss,n,0);
  tops.clear();
  for(I i=0;i<n;i++)dfs2(i);
  reverse(tops.begin(),tops.end());
  printf("%lli\n",res);
  for(auto i:tops)printf("%i ",i+1);
}