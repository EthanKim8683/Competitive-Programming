#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I MAX=1e9;
vector<I>adjs[N];
I dp[N][2];
void dfs(I a,I p=-1){
  dp[a][0]=dp[a][1]=0;
  I cnt=0,cst=0;
  for(auto b:adjs[a])if(b!=p){
    dfs(b,a);
    dp[a][0]+=dp[b][0];
    dp[a][1]+=dp[b][1];
    cst=min(cst,dp[b][0]-dp[b][1]);
    cnt++;
  }
  if(cnt==0)dp[a][0]=0,dp[a][1]=1;
  if(cnt>1)dp[a][0]=MAX,dp[a][1]+=cst;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<n-1;i++){
      I x,y;cin>>x>>y,x--,y--;
      adjs[x].push_back(y);
      adjs[y].push_back(x);
    }
    if(n==1){printf("0\n");continue;}
    I r=0;
    for(;r<n;r++)if(adjs[r].size()>2)break;
    if(r==n){printf("1\n");continue;}
    dfs(r);
    printf("%i\n",dp[r][1]);
  }
}
/*
at every intersection, at most one subtree can contain zero queried nodes since
the queried nodes in the other subtrees can be used to distinguish nodes in
said subtree
 
we can use tree dynamic programming to find the minimum number of queried nodes
required given this property
*/