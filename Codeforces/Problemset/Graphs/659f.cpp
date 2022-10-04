#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=1000;
const I M=1000;

I dx[]{-1,1,0,0},dy[]{0,0,-1,1};
I tabs[N*M];
I pars[N*M];
I inds[N*M];
B viss[N*M];
Lli ress[N*M];
I cnt=0;
I tot;
I n,m;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m;
}

I ind(I i,I j){
  return i*m+j;
}

pair<I,I>exp(I x){
  return{x/m,x%m};
}

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

I siz(I i){
  return -pars[fnd(i)];
}

B cmp(I a,I b){
  return tabs[a]>tabs[b];
}

void dfs(I i,Lli r){
  if(!viss[i]||ress[i]||cnt>=tot)return;
  ress[i]=r,cnt++;
  auto[x,y]=exp(i);
  for(I j=0;j<4;j++){
    I z=x+dx[j],w=y+dy[j];
    if(!bnd(z,w))continue;
    dfs(ind(z,w),r);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli k;cin>>n>>m>>k;
  fill_n(pars,n*m,-1);
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)
    cin>>tabs[ind(i,j)];
  iota(inds,inds+n*m,0);
  sort(inds,inds+n*m,cmp);
  for(I i=0;i<n*m;i++){
    I j=inds[i];
    auto[x,y]=exp(j);
    viss[j]=1;
    for(I k=0;k<4;k++){
      I z=x+dx[k],w=y+dy[k];
      if(!bnd(z,w))continue;
      I l=ind(z,w);
      if(!viss[l])continue;
      uni(j,l);
    }
    I tab=tabs[j];
    if(k%tab)continue;
    if(siz(j)<k/tab)continue;
    tot=k/tab,dfs(j,tab);
    printf("YES\n");
    for(I i=0;i<n;i++){
      for(I j=0;j<m;j++)
        printf("%lli ",ress[ind(i,j)]);
      printf("\n");
    }
    exit(0);
  }
  printf("NO\n");
}