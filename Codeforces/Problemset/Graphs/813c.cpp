#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

vector<I>adjs[N];
I deps[N],maxs[N];
I tbegs[N],tends[N];
I dep=0,t=0;

void dfs(I a,I p=-1){
  tbegs[a]=t++;
  deps[a]=maxs[a]=dep++;
  for(auto b:adjs[a]){
    if(b==p)continue;
    dfs(b,a);
    maxs[a]=max(maxs[a],maxs[b]);
  }
  dep--;
  tends[a]=t;
}

B anc(I a,I b){
  return tbegs[a]<=tbegs[b]&&tends[a]>=tends[b];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,x;cin>>n>>x,x--;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs(0);
  I res=0;
  for(I i=0;i<n;i++){
    if(!anc(i,x))continue;
    if(deps[x]-deps[i]>=deps[i]-deps[0])continue;
    res=max(res,maxs[i]);
  }
  printf("%i\n",res*2);
  return 0;
}