#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
I a_arr[N];
map<I,I>pres;
I dp[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    pres.clear();
    fill_n(dp,n+1,0);
    I cur=0;
    for(I i=0;i<n;i++){
      pres[cur]=i;
      I a=a_arr[i];
      cur^=a;
      if(pres.count(cur))dp[i+1]=max(dp[i+1],dp[pres[cur]]+1);
      dp[i+1]=max(dp[i+1],dp[i]);
    }
    printf("%i\n",n-dp[n]);
  }
}