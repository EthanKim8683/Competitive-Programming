#include<iostream>
#include<cstdio>
#include<tuple>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=2e5;
const I M=5e5;

I pars[N];
tuple<I,I,B>coms[M];
vector<I>adjs[N];
B cols[N];
B viss[N];
I tots[2];

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

B con(I a,I b){
  return fnd(a)==fnd(b);
}

I siz(I i){
  return -pars[fnd(i)];
}

B dfs(I a,B c){
  if(viss[a])return cols[a]==c;
  viss[a]=1,cols[a]=c;
  tots[c]+=siz(a);
  B res=1;
  for(auto b:adjs[a])res&=dfs(b,!c);
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    fill_n(pars,n,-1),fill_n(viss,n,0);
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I k=0;k<m;k++){
      I i,j;S c;cin>>i>>j>>c,i--,j--;
      if(c=="imposter")coms[k]={i,j,1};
      if(c=="crewmate")coms[k]={i,j,0},uni(i,j);
    }
    B vld=1;
    for(I k=0;k<m&&vld;k++){
      auto[i,j,c]=coms[k];
      if(c){
        vld&=!con(i,j);
        i=fnd(i),j=fnd(j);
        adjs[i].push_back(j);
        adjs[j].push_back(i);
      }
    }
    if(!vld){printf("-1\n");continue;}
    I res=0;
    for(I i=0;i<n&&vld;i++){
      if(i!=fnd(i))continue;
      tots[0]=tots[1]=0;
      vld&=dfs(i,cols[i]);
      res+=max(tots[0],tots[1]);
    }
    if(!vld){printf("-1\n");continue;}
    printf("%i\n",res);
  }
  return 0;
}