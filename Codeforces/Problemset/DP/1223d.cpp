#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=3e5;
const I MAX=1e9;
const I MIN=-1e9;
I a_arr[N];
pair<I,I>rngs[N];
I dp[N+1];
vector<I>stks;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    fill_n(rngs,n,pair<I,I>{MAX,MIN});
    for(I i=0;i<n;i++){
      I a=a_arr[i]-1;
      rngs[a].first=min(rngs[a].first,i);
      rngs[a].second=max(rngs[a].second,i);
    }
    I cnt=0,siz=0;
    stks.clear();
    for(I i=0;i<n;i++){
      auto[low,upp]=rngs[i];
      if(low==MAX)continue;
      if(stks.size()&&stks.back()>low)stks.clear();
      stks.push_back(upp);
      siz=max(siz,(I)stks.size());
      cnt++;
    }
    printf("%i\n",cnt-siz);
  }
}