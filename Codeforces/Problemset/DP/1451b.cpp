#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=100;

I dp[N+1];

void fix(I&i){
  i=min(i,2);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,q;cin>>n>>q;
    S s;cin>>s;
    while(q--){
      I l,r;cin>>l>>r,l--,r--;
      fill(dp+l,dp+r+1+1,0);
      dp[l]=1;
      for(auto c:s)for(I i=r;i>=l;i--)if(c==s[i])fix(dp[i+1]+=dp[i]);
      printf("%s\n",dp[r+1]>1?"YES":"NO");
    }
  }
}