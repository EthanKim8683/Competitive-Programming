#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100000;
const I M=100000;
I ps[M+1];
vector<I>dp;
I liss1[M],liss2[M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r,l--,r--;
    ps[l]++,ps[r+1]--;
  }
  for(I i=0;i<m;i++)ps[i+1]+=ps[i];
  for(I i=0;i<m;i++){
    liss1[i]=dp.size();
    auto it=upper_bound(dp.begin(),dp.end(),ps[i]);
    if(it==dp.end())dp.push_back(ps[i]);
    else *it=ps[i];
  }
  dp.clear();
  for(I i=m-1;i>=0;i--){
    auto it=upper_bound(dp.begin(),dp.end(),ps[i]);
    if(it==dp.end())dp.push_back(ps[i]);
    else *it=ps[i];
    liss2[i]=dp.size();
  }
  I res=0;
  for(I i=0;i<m;i++)res=max(res,liss1[i]+liss2[i]);
  printf("%i\n",res);
}