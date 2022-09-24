#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I LOGN=17;

vector<I>adjs[N];
I tbegs[N],tends[N];
I ancs[N][LOGN];
I deps[N];
I t=0;

void dfs(I a,I p,I d=0){
  deps[a]=d;
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  tbegs[a]=t++;
  for(auto b:adjs[a])if(b!=p)dfs(b,a,d+1);
  tends[a]=t;
}

B anc(I a,I b){
  return tbegs[a]<=tbegs[b]&&tends[a]>=tends[b];
}

I lca(I a,I b){
  if(anc(a,b))return a;
  if(anc(b,a))return b;
  for(I i=LOGN-1;i>=0;i--)if(!anc(ancs[a][i],b))a=ancs[a][i];
  return ancs[a][0];
}

I cnt(I a,I b,I c){
  I ab=lca(a,b),bc=lca(b,c),ca=lca(c,a);
  if(bc==ca)return deps[ab]+deps[c]-deps[bc]*2+1;
  return deps[c]-max(deps[bc],deps[ca])+1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=1;i<n;i++){
    I p;cin>>p,p--;
    adjs[p].push_back(i);
    adjs[i].push_back(p);
  }
  dfs(0,0);
  while(q--){
    I a,b,c;cin>>a>>b>>c,a--,b--,c--;
    I res=0;
    res=max(res,cnt(a,b,c));
    res=max(res,cnt(a,c,b));
    res=max(res,cnt(b,a,c));
    res=max(res,cnt(b,c,a));
    res=max(res,cnt(c,a,b));
    res=max(res,cnt(c,b,a));
    printf("%i\n",res);
  }
  return 0;
}