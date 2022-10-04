#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=100000;
const I MAX=1e9;

vector<I>adjs1[N],adjs2[N];
I a_arr[N];
I diss[N];
I inds[N];
I viss[N];
vector<I>ress;
queue<I>que;

void dfs(I a,I r){
  if(viss[a]!=-1)return;
  viss[a]=r;
  for(auto b:adjs2[a])dfs(b,r);
}

void add(I d,I i){
  if(d>=diss[i])return;
  diss[i]=d,que.push(i);
}

B cmp(I a,I b){
  return diss[a_arr[a]]>diss[a_arr[b]];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(diss,n,MAX);
  fill_n(viss,n,-1);
  for(I i=0;i<m;i++){
    I p,q;cin>>p>>q,p--,q--;
    adjs1[q].push_back(p);
    adjs2[p].push_back(q);
  }
  for(I i=0;i<n;i++){I a;cin>>a,a_arr[i]=a-1;}
  for(I i=0;i<n;i++)if(!adjs1[i].size())add(0,i);
  while(que.size()){
    I a=que.front();que.pop();
    for(auto b:adjs2[a])add(diss[a]+1,b);
  }
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  for(I i=0;i<n;i++){
    I j=inds[i],a=a_arr[j];
    if(viss[j]!=-1){
      if(viss[j]==a)continue;
      printf("-1\n"),exit(0);
    }
    dfs(a,a);
    ress.push_back(a);
  }
  printf("%i\n",ress.size());
  for(auto i:ress)printf("%i\n",i+1);
}