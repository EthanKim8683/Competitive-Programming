#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;
using Lf=long double;
using B=bool;
using Lli=long long int;

const I N=100;
const I MAX=1e9;

vector<I>adjs1[N],adjs2[N],adjs3[N];
queue<I>que;
I diss[N];
vector<I>tops1,tops2;
B viss1[N],viss2[N];
Lli dp1[N],dp2[N];
Lli cons[N];

void add(I d,I i,I p){
  if(d>diss[i])return;
  if(d==diss[i]){adjs2[i].push_back(p);return;}
  adjs2[i].clear(),adjs2[i].push_back(p);
  que.push(i),diss[i]=d;
}

void dfs1(I a){
  if(viss1[a])return;
  viss1[a]=1;
  for(auto b:adjs2[a])dfs1(b);
  tops1.push_back(a);
}

void dfs2(I a){
  if(viss2[a])return;
  viss2[a]=1;
  for(auto b:adjs3[a])dfs2(b);
  tops2.push_back(a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(diss,n,MAX);
  for(I i=0;i<m;i++){
    I v,u;cin>>v>>u,v--,u--;
    adjs1[v].push_back(u);
    adjs1[u].push_back(v);
  }
  add(0,0,-1);
  adjs2[0].clear();
  while(que.size()){
    I a=que.front();que.pop();
    for(auto b:adjs1[a])add(diss[a]+1,b,a);
  }
  for(I i=0;i<n;i++)for(auto j:adjs2[i])
    adjs3[j].push_back(i);
  dfs1(n-1),dfs2(0);
  reverse(tops1.begin(),tops1.end());
  reverse(tops2.begin(),tops2.end());
  dp1[n-1]=1,dp2[0]=1;
  for(auto i:tops1)for(auto j:adjs2[i])dp1[j]+=dp1[i];
  for(auto i:tops2)for(auto j:adjs3[i])dp2[j]+=dp2[i];
  for(I i=0;i<n;i++)cons[i]=dp1[i]*dp2[i];
  Lf res=1;
  for(I i=1;i<n-1;i++)res=max(res,(Lf)cons[i]*2/cons[n-1]);
  printf("%.12Lf\n",res);
  return 0;
}