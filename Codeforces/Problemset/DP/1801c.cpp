#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=200000;
const I K=200000;
I a_arr[K];
vector<I>stks[N];
I inds[N];
map<I,I>dp;
B cmp(I a,I b){
  return stks[a].front()<stks[b].front();
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++){
      I k;cin>>k;
      for(I j=0;j<k;j++)cin>>a_arr[j];
      stks[i].clear();
      for(I j=k-1;j>=0;j--){
        I a=a_arr[j];
        while(stks[i].size()&&stks[i].back()<=a)stks[i].pop_back();
        stks[i].push_back(a);
      }
    }
    iota(inds,inds+n,0);
    sort(inds,inds+n,cmp);
    dp.clear();
    for(I i=0;i<n;i++){
      I j=inds[i],a=stks[j].front(),len=1;
      dp[a]=max(dp[a],(I)stks[j].size());
      for(auto b:stks[j]){
        auto it=dp.lower_bound(b);
        if(it!=dp.begin())dp[a]=max(dp[a],prev(it)->second+len);
        len++;
      }
    }
    I res=0;
    for(auto[a,len]:dp)res=max(res,len);
    printf("%i\n",res);
  }
}