#include<iostream>
#include<cstdio>
#include<unordered_set>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I M=3e5;

pair<I,I>edgs[M];
unordered_set<I>invs[N];
B viss[N];
I pars[N];
I ress[N];
I cnt;

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
  cnt--;
}

B con(I a,I b){
  return fnd(a)==fnd(b);
}

I siz(I i){
  return -pars[fnd(i)];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(pars,n,-1);
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    invs[a].insert(b);
    invs[b].insert(a);
    edgs[i]={a,b};
  }
  cnt=n;
  I tot=0;
  for(I i=0;i<n;i++){
    if(viss[i])continue;
    if(tot>=3){printf("-1\n");return 0;}
    tot++;
    for(I j=0;j<n;j++)
      if(invs[i].find(j)==invs[i].end())uni(i,j),viss[j]=1;
  }
  if(tot!=3){printf("-1\n");return 0;}
  for(I i=0;i<m;i++){
    auto[a,b]=edgs[i];
    if(con(a,b)){printf("-1\n");return 0;}
  }
  for(I i=0;i<n;i++)
    if(n-siz(i)!=invs[i].size()){printf("-1\n");return 0;}
  I cur=0;
  for(I i=0;i<n;i++)if(i==fnd(i))ress[i]=cur++;
  for(I i=0;i<n;i++)printf("%i ",ress[fnd(i)]+1);
  return 0;
}