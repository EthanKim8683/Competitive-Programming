#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=3e5;
const I M=3e5;
tuple<I,I,I>edgs[M];
map<I,I>dp[N];
void cmb(I&a,I b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v,w;cin>>u>>v>>w;
    edgs[i]={w,u-1,v-1};
  }
  sort(edgs,edgs+m);
  for(I i=0;i<n;i++)dp[i][-1]=0;
  I res=0;
  for(I i=0;i<m;i++){
    auto[w,u,v]=edgs[i];
    I a=prev(dp[u].lower_bound(w))->second+1;
    I b=prev(dp[v].lower_bound(w))->second;
    cmb(dp[v][w],max(a,b));
    cmb(res,a);
  }
  printf("%i\n",res);
}