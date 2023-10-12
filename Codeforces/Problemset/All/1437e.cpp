#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=5e5;
const I K=N;
const I MIN=-1e9;
I a_arr[N];
I b_arr[K];
B invs[N];
vector<pair<I,I>>rngs;
vector<I>dp;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<k;i++)cin>>b_arr[i];
  I upp=MIN;
  for(I i=0;i<k;i++){
    I b=b_arr[i]-1,cur=a_arr[b]-b;
    if(upp>cur)printf("-1"),exit(0);
    upp=max(upp,cur);
  }
  for(I i=0;i<k;i++)invs[b_arr[i]-1]=1;
  B pre=invs[0];I j=0;
  for(I i=1;i<n;i++){
    B cur=invs[i];
    if(cur!=pre){
      if(pre==0)rngs.push_back({j,i-1});
      j=i;
    }
    pre=cur;
  }
  if(pre==0)rngs.push_back({j,n-1});
  I res=0;
  for(auto[l,r]:rngs){
    dp.clear();
    for(I i=l;i<=r;i++){
      if(l-1>=0&&a_arr[l-1]-(l-1)>a_arr[i]-i)continue;
      if(r+1<n&&a_arr[r+1]-(r+1)<a_arr[i]-i)continue;
      auto it=upper_bound(dp.begin(),dp.end(),a_arr[i]-i);
      if(it==dp.end())dp.push_back(a_arr[i]-i);
      else*it=a_arr[i]-i;
    }
    res+=r+1-l-dp.size();
  }
  printf("%i\n",res);
}