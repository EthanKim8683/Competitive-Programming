#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
vector<I>adjs[N];
I dp1[N],dp2[N];
void dfs(I a){
  for(auto b:adjs[a]){
    dfs(b);
    dp1[a]=max(dp1[a],dp1[b]);
    dp2[a]+=max(dp1[b],dp2[b]);
  }
  dp1[a]++;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=1;i<n;i++){
    I p;cin>>p,p--;
    adjs[p].push_back(i);
  }
  dfs(0);
  printf("%i\n",max(dp1[0],dp2[0]));
}