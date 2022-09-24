#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using S=string;

const I K=2000;
const I MAX=1e9;

I cnts[26];
vector<I>facs;
I dp[K+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    S s;cin>>s;
    fill_n(cnts,26,0);
    facs.clear();
    for(auto c:s)cnts[c-'a']++;
    for(I i=1;i*i<=k;i++){
      if(k%i==0){
        I j=k/i;
        facs.push_back(i);
        if(j!=i)facs.push_back(j);
      }
    }
    I res=0;
    for(auto i:facs){
      if(i>n)continue;
      fill_n(dp,i+1,0);
      dp[0]=MAX;
      for(I j=0;j<26;j++){
        I cnt=cnts[j];
        if(!cnt)continue;
        for(I k=i;k>=0;k--){
          if(!dp[k])continue;
          for(I l=1;l<=cnt&&k+l<=i;l++)
            dp[k+l]=max(dp[k+l],min(dp[k],cnt/l));
        }
      }
      res=max(res,i*dp[i]);
    }
    printf("%i\n",res);
  }
  return 0;
}