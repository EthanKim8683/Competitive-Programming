#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using C=char;

const I N=500;
const I M=N*(N-1)/2;

I degs[N];
C ress[N];
I pars[N];
I cnts[N];
pair<I,I>edgs[M];

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

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(pars,n,-1);
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    degs[u]++,degs[v]++;
    edgs[i]={u,v};
  }
  for(I i=0;i<n;i++)if(degs[i]==n-1)ress[i]='b';
  for(I i=0;i<m;i++){
    auto[u,v]=edgs[i];
    if(ress[u]||ress[v])continue;
    uni(u,v);
  }
  for(I i=0;i<m;i++){
    auto[u,v]=edgs[i];
    if(ress[u]||ress[v])continue;
    cnts[fnd(u)]++;
  }
  for(I i=0;i<n;i++){
    if(ress[i]||i!=fnd(i))continue;
    I s=siz(i);
    if(cnts[i]!=s*(s-1)/2){printf("No\n");return 0;}
  }
  I cnt=0;
  for(I i=0;i<n;i++){
    if(ress[i]||i!=fnd(i))continue;
    if(cnt==0)ress[i]='a';
    if(cnt==1)ress[i]='c';
    if(cnt>=2){printf("No\n");return 0;}
    cnt++;
  }
  printf("Yes\n");
  for(I i=0;i<n;i++)printf("%c",ress[fnd(i)]);
  return 0;
}