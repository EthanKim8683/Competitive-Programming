#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=1e5;
const I MAX=1e9;

I dp[N+1];
set<I>inds[26][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    S s;cin>>s;
    S t;cin>>t;
    I n=s.size();
    I m=t.size();
    fill_n(dp,n+1,MAX);
    for(I i=0;i<26;i++)for(I j=0;j<2;j++)inds[i][j].clear();
    for(I i=0;i<n;i++)inds[s[i]-'a'][i%2].insert(i);
    B res=0;
    dp[n]=m-1;
    for(I i=n;i>=0;i--){
      I j=dp[i];
      if(j==MAX)continue;
      if(j==-1){res=1;continue;}
      I k=t[j]-'a',l=!(i%2);
      auto it=inds[k][l].lower_bound(i);
      if(it==inds[k][l].begin())continue;
      I o=*--it;
      dp[o]=min(dp[o],j-1);
    }
    printf("%s\n",res?"YES":"NO");
  }
}