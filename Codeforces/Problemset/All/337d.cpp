#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100000;
const I M=100000;
const I MIN=-1e9;
I p_arr[M];
vector<I>adjs[N];
I dp[N][2];
multiset<I>vals;
void cmb(I&a,I b){
  a=max(a,b);
}
void dfs1(I a,I p=-1){
  for(auto b:adjs[a])if(b!=p){
    dfs1(b,a);
    cmb(dp[a][0],dp[b][0]+1);
  }
}
void dfs2(I a,I p=-1){
  vals.clear();
  for(auto b:adjs[a])if(b!=p)vals.insert(dp[b][0]);
  for(auto b:adjs[a])if(b!=p){
    vals.erase(vals.find(dp[b][0]));
    cmb(dp[b][1],dp[a][1]+1);
    if(vals.size())cmb(dp[b][1],*vals.rbegin()+2);
    vals.insert(dp[b][0]);
  }
  for(auto b:adjs[a])if(b!=p)dfs2(b,a);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+N*2,MIN);
  I n,m,d;cin>>n>>m>>d;
  for(I i=0;i<m;i++)cin>>p_arr[i];
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  for(I i=0;i<n;i++)dp[p_arr[i]-1][0]=dp[p_arr[i]-1][1]=0;
  dfs1(0),dfs2(0);
  I res=0;
  for(I i=0;i<n;i++)res+=max(dp[i][0],dp[i][1])<=d;
  printf("%i\n",res);
}