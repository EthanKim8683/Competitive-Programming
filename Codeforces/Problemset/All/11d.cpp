#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=19;
vector<I>adjs[N];
Lli dp[1<<N][N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  Lli res=0;
  for(I i=0;i<n;i++)dp[1<<i][i]=1;
  for(I i=0;i<(1<<n);i++){
    I j=__builtin_ctz(i);
    for(I a=0;a<n;a++)for(auto b:adjs[a]){
      if(b==j&&__builtin_popcount(i)>=3)res+=dp[i][a];
      if(b<=j)continue;
      if(i>>b&1)continue;
      dp[i|1<<b][b]+=dp[i][a];
    }
  }
  printf("%lli\n",res>>1);
}