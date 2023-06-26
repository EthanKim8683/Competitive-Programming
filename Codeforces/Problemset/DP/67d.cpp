#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e6;
I x_arr[N];
I y_arr[N];
I inds[N];
vector<I>dp;
B cmp(I a,I b){
  return x_arr[a]<x_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x;cin>>x,x--;
    x_arr[x]=i;
  }
  for(I i=0;i<n;i++){
    I y;cin>>y,y--;
    y_arr[y]=i;
  }
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  for(I i=0;i<n;i++){
    I y=y_arr[inds[i]];
    auto it=lower_bound(dp.begin(),dp.end(),-y);
    if(it==dp.end())dp.push_back(-y);
    else*it=-y;
  }
  printf("%i\n",dp.size());
}