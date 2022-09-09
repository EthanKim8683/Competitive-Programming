#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;
const I MAX=1e9;

vector<pair<I,I>>adjs[N];
I dp[N][2];
vector<I>ress;
I res=MAX;

void dfs1(I a,I p=-1){
  for(auto[b,c]:adjs[a]){
    if(b==p)continue;
    dfs1(b,a);
    dp[a][0]+=dp[b][0]+!c;
    dp[a][1]+=dp[b][1]+c;
  }
}

void dfs2(I a,I p=-1){
  I inv=dp[a][1];
  if(inv<res)res=inv,ress.clear();
  if(inv==res)ress.push_back(a);
  for(auto[b,c]:adjs[a]){
    if(b==p)continue;
    dp[b][0]=dp[a][0]+c-!c;
    dp[b][1]=dp[a][1]-c+!c;
    dfs2(b,a);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I s,t;cin>>s>>t,s--,t--;
    adjs[s].push_back({t,0});
    adjs[t].push_back({s,1});
  }
  dfs1(0),dfs2(0);
  printf("%i\n",res);
  sort(ress.begin(),ress.end());
  for(auto i:ress)printf("%i ",i+1);
  return 0;
}