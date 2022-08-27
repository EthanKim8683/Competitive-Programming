#include<iostream>
#include<cstdio>
#include<algorithm>
#include<numeric>
#include<vector>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I N=1000;

I v_arr[N];
I inds[N];
Lli sums[N];
vector<I>adjs[N];

B cmp(I a,I b){
  return v_arr[a]>v_arr[b];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>v_arr[i];
  for(I i=0;i<m;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  for(I i=0;i<n;i++)
    for(auto j:adjs[i])
      sums[i]+=v_arr[j];
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  Lli res=0;
  for(I i=0;i<n;i++){
    I a=inds[i];
    res+=sums[a];
    for(auto b:adjs[a])
      sums[b]-=v_arr[a];
  }
  printf("%lli\n",res);
  return 0;
}