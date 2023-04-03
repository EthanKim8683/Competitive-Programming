#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const Lli MOD=998244353;
vector<I>adjs[N];
Lli facs[N];
Lli dfs(I a,I p=-1){
  I n=adjs[a].size();
  Lli res=n*facs[n-1]%MOD;
  for(auto b:adjs[a])if(b!=p)(res*=dfs(b,a))%=MOD;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  facs[0]=1;
  for(I i=1;i<n;i++)facs[i]=facs[i-1]*i%MOD;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  Lli res=n*facs[adjs[0].size()]%MOD;
  for(auto b:adjs[0])(res*=dfs(b,0))%=MOD;
  printf("%lli\n",res);
}