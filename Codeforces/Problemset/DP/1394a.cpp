#include<bits/stdc++.h>
 
using namespace std;
 
using I=int;
using Lli=long long int;
 
const I N=1e5;
 
I a_arr[N];
vector<I>upps,lows;
Lli ps1[N+1];
Lli ps2[N+1];
 
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,d,m;cin>>n>>d>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(a>m)upps.push_back(a);
    if(a<=m)lows.push_back(a);
  }
  sort(upps.begin(),upps.end(),greater<I>());
  sort(lows.begin(),lows.end(),greater<I>());
  I x=upps.size(),y=lows.size();
  for(I i=0;i<x;i++)ps1[i+1]=upps[i];
  for(I i=0;i<x;i++)ps1[i+1]+=ps1[i];
  for(I i=0;i<y;i++)ps2[i+1]=lows[i];
  for(I i=0;i<y;i++)ps2[i+1]+=ps2[i];
  Lli res=ps2[y];
  for(I i=1;i<=x&&(i-1)*d<=x-i+y;i++)res=max(res,ps1[i]+ps2[y-max((i-1)*d-(x-i),0)]);
  printf("%lli\n",res);
}