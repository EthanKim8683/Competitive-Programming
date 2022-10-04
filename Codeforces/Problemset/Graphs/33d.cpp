#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=1000;
const I M=1000;
const I LOGNM=11;

vector<I>adjs[N+M+1];
pair<I,I>cons[N];
tuple<I,I,I>fens[M];
B viss[N+M];
I ancs[N+M+1][LOGNM];
I tbegs[N+M+1];
I tends[N+M+1];
I deps[N+M+1];
I t=0;

B ins(Lli r,Lli ax,Lli ay,Lli bx,Lli by){
  Lli dx=ax-bx,dy=ay-by;
  return dx*dx+dy*dy<=r*r;
}

void dfs(I a,I p,I d=0){
  tbegs[a]=t++;
  deps[a]=d;
  ancs[a][0]=p;
  for(I i=1;i<LOGNM;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  for(auto b:adjs[a])dfs(b,a,d+1);
  tends[a]=t++;
}

B anc(I a,I b){
  return tbegs[a]<=tbegs[b]&&tends[a]>=tends[b];
}

I lca(I a,I b){
  if(anc(a,b))return a;
  if(anc(b,a))return b;
  for(I i=LOGNM-1;i>=0;i--)if(!anc(ancs[a][i],b))a=ancs[a][i];
  return ancs[a][0];
}

I dis(I a,I b){
  if(a==b)return 0;
  return deps[a]+deps[b]-2*deps[lca(a,b)]-2;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  for(I i=0;i<n;i++){
    I kx,ky;cin>>kx>>ky;
    cons[i]={kx,ky};
  }
  for(I i=0;i<m;i++){
    I r,cx,cy;cin>>r>>cx>>cy;
    fens[i]={r,cx,cy};
  }
  sort(fens,fens+m);
  for(I i=0;i<m;i++){
    auto[ir,ix,iy]=fens[i];
    for(I j=0;j<n;j++)if(!viss[j]){
      auto[jx,jy]=cons[j];
      if(!ins(ir,ix,iy,jx,jy))continue;
      viss[j]=1;
      adjs[n+i].push_back(j);
    }
    for(I j=0;j<i;j++)if(!viss[n+j]){
      auto[jr,jx,jy]=fens[j];
      if(!ins(ir,ix,iy,jx,jy))continue;
      viss[n+j]=1;
      adjs[n+i].push_back(n+j);
    }
  }
  for(I i=0;i<n;i++)if(!viss[i]){
    viss[i]=1;
    adjs[n+m].push_back(i);
  }
  for(I i=0;i<m;i++)if(!viss[n+i]){
    viss[n+i]=1;
    adjs[n+m].push_back(n+i);
  }
  dfs(n+m,n+m);
  while(k--){
    I a,b;cin>>a>>b;
    printf("%i\n",dis(a-1,b-1));
  }
}