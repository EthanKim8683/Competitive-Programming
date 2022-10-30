#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=1e6;

I dp[N];
multiset<I>vals;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  for(I i=1,l=0,r=0;i<n;i++){
    if(i<=r)dp[i]=min(r-i+1,dp[i-l]);
    while(i+dp[i]<n&&s[dp[i]]==s[i+dp[i]])dp[i]++;
    if(i+dp[i]-1>r)l=i,r=i+dp[i]-1;
  }
  for(I i=1;i<n;i++)vals.insert(dp[i]);
  I res=0;
  for(I i=n-1;i>0;i--){
    I cur=dp[i];
    vals.erase(vals.find(cur));
    if(cur==n-i&&vals.lower_bound(cur)!=vals.end())res=max(res,cur);
  }
  if(!res)printf("Just a legend"),exit(0);
  printf("%s\n",s.substr(0,res).c_str());
}