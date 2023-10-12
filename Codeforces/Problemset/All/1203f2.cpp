#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100;
const I R=30000;
const I MIN=-1e9;
vector<pair<I,I>>poss;
vector<tuple<I,I,I>>negs;
I dp[2*R+1][N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(2*R+1)*(N+1),MIN);
  I n,r;cin>>n>>r;
  for(I i=0;i<n;i++){
    I a,b;cin>>a>>b;
    if(b>=0)poss.push_back({a,b});
    if(b<0)negs.push_back({a+b,a,b});
  }
  sort(poss.begin(),poss.end());
  sort(negs.rbegin(),negs.rend());
  I cnt=0;
  for(auto[a,b]:poss)if(r>=a)r+=b,cnt++;
  dp[r][0]=cnt;
  for(I i=r;i>=0;i--)for(I j=0;j<negs.size();j++){
    auto[key,a,b]=negs[j];
    if(i>=a&&i+b>=0)dp[i+b][j+1]=max(dp[i+b][j+1],dp[i][j]+1);
    dp[i][j+1]=max(dp[i][j+1],dp[i][j]);
  }
  I res=MIN;
  for(I i=0;i<=r;i++)for(I j=0;j<=negs.size();j++)res=max(res,dp[i][j]);
  printf("%i\n",res);
}
/*
initially, Polycarp should only complete projects that yield positive rating
change, as, if a project can be completed after a negative rating change, it
can also be completed before the rating change

for projects with positive rating changes, the projects can be completed
greedily in non-decreasing order of rating, since, if a project with higher
required rating can be completed, so can projects with lower required ratings

for projects with negative rating changes, the projects should be sorted
in non-increasing order of minimum rating after change

this ensures that, when processing projects in order (so that no project is
completed twice), no project that is completed in the maximum subset is
skipped in favor of another project

the logic is to work backwards from the same logic used for the set of
positive rating change projects
*/