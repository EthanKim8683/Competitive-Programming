#include<iostream>
#include<cstdio>
#include<vector>
#include<set>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=150000;
const Lli MAX=1e18;

I n_arr[4];
I csts[4][N];
vector<I>invs[3][N];
Lli dp[4][N];
multiset<Lli>pres;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  for(I i=0;i<4;i++)cin>>n_arr[i];
  for(I i=0;i<4;i++)for(I j=0;j<n_arr[i];j++)cin>>csts[i][j];
  for(I i=0;i<3;i++){
    I m;cin>>m;
    for(I j=0;j<m;j++){
      I x,y;cin>>x>>y;
      invs[i][y-1].push_back(x-1);
    }
  }
  for(I i=0;i<n_arr[0];i++)dp[0][i]=csts[0][i];
  for(I i=0;i<3;i++){
    pres.clear();
    for(I j=0;j<n_arr[i];j++)pres.insert(dp[i][j]);
    for(I j=0;j<n_arr[i+1];j++){
      for(auto k:invs[i][j])pres.erase(pres.find(dp[i][k]));
      dp[i+1][j]=pres.size()?*pres.begin()+csts[i+1][j]:MAX;
      for(auto k:invs[i][j])pres.insert(dp[i][k]);
    }
  }
  Lli res=MAX;
  for(I i=0;i<n_arr[3];i++)res=min(res,dp[3][i]);
  if(res==MAX)printf("-1\n");
  else printf("%lli\n",res);
  return 0;
}