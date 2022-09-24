#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1e4;
const I M=1e5;
const I D=1e9;
const I MAX=1e9;

vector<pair<I,I>>adjs[N];
I cons1[N],cons2[N];
I diss[N+1];
queue<I>que;
I n;

void add(I d,I i){
  if(d>=diss[i])return;
  que.push(i),diss[i]=d;
}

B bfs(I x){
  fill_n(diss,n,MAX);
  for(I i=0;i<n;i++)if(cons1[i]==N)add(0,i);
  diss[N]=MAX;
  while(que.size()){
    I a=que.front();que.pop();
    if(a==N)return 1;
    for(auto[b,d]:adjs[a])if(d<=x)
      add(diss[a]+1,cons2[b]);
  }
  return 0;
}

B dfs(I a,I x){
  if(a==N)return 1;
  for(auto[b,d]:adjs[a])if(d<=x){
    I c=cons2[b];
    if(diss[a]+1!=diss[c]||!dfs(c,x))continue;
    cons1[a]=b,cons2[b]=a;
    return 1;
  }
  diss[a]=MAX;
  return 0;
}

I hpk(I x){
  fill_n(cons1,n,N),fill_n(cons2,n,N);
  I res=0;
  while(bfs(x))for(I i=0;i<n;i++)res+=cons1[i]==N&&dfs(i,x);
  return res;
}

I fnd(){
  I l=0,r=D+1;
  while(l<r){
    I m=l+(r-l)/2;
    if(hpk(m)==n)r=m;
    else l=m+1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v,d;cin>>u>>v>>d;
    adjs[u-1].push_back({v-1,d});
  }
  I res=fnd();
  if(res==D+1)printf("-1\n"),exit(0);
  printf("%i\n",res);
  return 0;
}