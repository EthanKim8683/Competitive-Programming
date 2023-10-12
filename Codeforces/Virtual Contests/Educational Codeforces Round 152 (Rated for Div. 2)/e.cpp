#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e6;
I p_arr[N];
vector<I>lows,upps;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>p_arr[i];
  Lli res=0,cur=0;
  for(I i=0;i<n;i++){
    while(upps.size()&&p_arr[upps.back()]<p_arr[i]){
      I a=upps.back();
      upps.pop_back();
      auto it=upper_bound(lows.begin(),lows.end(),a);
      if(it==lows.begin())continue;
      I b=*prev(it),c=upps.size()?upps.back():-1;
      cur-=max(b-c,0);
    }
    while(lows.size()&&p_arr[lows.back()]>p_arr[i]){
      I a=lows.back();
      lows.pop_back();
      auto it=upper_bound(upps.begin(),upps.end(),a);
      if(it==upps.end())continue;
      I b=lows.size()?lows.back():it==upps.begin()?-1:*prev(it);
      cur-=max(a-b,0);
    }
    if(lows.size()){
      I b=lows.back(),c=upps.size()?upps.back():-1;
      cur+=max(b-c,0);
    }
    upps.push_back(i),lows.push_back(i),res+=cur;
  }
  printf("%lli\n",res);
}