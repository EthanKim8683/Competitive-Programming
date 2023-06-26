#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I M=1e5;
const Lli MAX=1e18;
I a_arr[M];
vector<I>srcs[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++)cin>>a_arr[i];
  Lli bef=0;
  for(I i=0;i+1<m;i++){
    I a=a_arr[i]-1,b=a_arr[i+1]-1;
    if(a==b)continue;
    srcs[a].push_back(b);
    srcs[b].push_back(a);
    bef+=abs(a-b);
  }
  Lli res=bef;
  for(I i=0;i<n;i++){
    if(!srcs[i].size())continue;
    nth_element(srcs[i].begin(),srcs[i].begin()+srcs[i].size()/2,srcs[i].end());
    I k=srcs[i][srcs[i].size()/2];
    Lli cur=bef;
    for(auto j:srcs[i])cur+=abs(j-k)-abs(j-i);
    res=min(res,cur);
  }
  printf("%lli\n",res);
}