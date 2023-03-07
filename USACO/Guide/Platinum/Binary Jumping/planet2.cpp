#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I LOGN=18;
I t_arr[N];
vector<I>adjs[N];
I inds[N];
I lens[N];
I deps[N];
B viss[N];
I ancs[N][LOGN];
void dfs(I a,I d=0){
  viss[a]=1;
  deps[a]=d;
  for(auto b:adjs[a])if(!viss[b])dfs(b,d+1);
}
void fld(I x){
  I y=x;
  do{
    x=t_arr[x];
    y=t_arr[t_arr[y]];
  }while(x!=y);
  I i=0;
  do{
    viss[x]=1;
    inds[x]=i++;
    x=t_arr[x];
  }while(x!=y);
  do{
    dfs(x);
    lens[x]=i;
    x=t_arr[x];
  }while(x!=y);
}
I jmp(I i,I j){
  for(I k=0;k<LOGN;k++)if(j>>k&1)i=ancs[i][k];
  return i;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=0;i<n;i++){I t;cin>>t,t_arr[i]=t-1;}
  for(I i=0;i<n;i++)adjs[t_arr[i]].push_back(i);
  for(I i=0;i<n;i++)if(!viss[i])fld(i);
  for(I i=0;i<n;i++)ancs[i][0]=t_arr[i];
  for(I i=1;i<LOGN;i++)for(I j=0;j<n;j++)ancs[j][i]=ancs[ancs[j][i-1]][i-1];
  while(q--){
    I a,b;cin>>a>>b,a--,b--;
    I dep1=deps[a],dep2=deps[b];
    if(dep2==0){
      I c=jmp(a,dep1);
      I len=lens[c],dis2=(inds[b]-inds[c]+len)%len;
      I d=jmp(c,dis2);
      if(d!=b){printf("-1\n");continue;}
      printf("%i\n",dep1+dis2);
    }
    if(dep2!=0){
      I dis=dep1-dep2;
      if(dis<0){printf("-1\n");continue;}
      I c=jmp(a,dis);
      if(c!=b){printf("-1\n");continue;}
      printf("%i\n",dis);
    }
  }
}