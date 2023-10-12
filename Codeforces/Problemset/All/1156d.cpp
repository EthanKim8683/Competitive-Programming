#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200000;
vector<pair<I,I>>adjs[N];
Lli dp1[N][4],dp2[N][4];
void dfs1(I a,I p=-1){
  for(auto[b,c]:adjs[a])if(b!=p){
    dfs1(b,a);
    if(c==0)dp1[a][0]+=dp1[b][0]+1,dp1[a][2]+=dp1[b][2]+dp1[b][3];
    if(c==1)dp1[a][1]+=dp1[b][0]+dp1[b][1],dp1[a][3]+=dp1[b][3]+1;
  }
}
void dfs2(I a,I p=-1){
  for(auto[b,c]:adjs[a])if(b!=p){
    if(c==0)dp2[b][0]+=dp2[a][0]+dp1[a][0]-dp1[b][0],dp2[a][2]+=dp2[a][2]+dp1[a][2]-dp1[b][2]+dp2[a][3]+dp1[a][3]-dp1[b][3];
    if(c==1)dp2[b][1]+=dp2[a][0]+dp1[a][0]-dp1[b][0]+dp2[a][1]+dp1[a][1]-dp1[b][1],dp2[b][3]+=dp2[a][3]+dp1[a][3]-dp1[b][3];
    dfs2(b,a);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I x,y,c;cin>>x>>y>>c,x--,y--;
    adjs[x].push_back({y,c});
    adjs[y].push_back({x,c});
  }
  dfs1(0),dfs2(0);
  Lli res=0;
  for(I i=0;i<n;i++)res+=dp1[i][0]+dp1[i][1]+dp1[i][3]+dp2[i][0]+dp2[i][1]+dp2[i][3];
  printf("%lli\n",res);
}