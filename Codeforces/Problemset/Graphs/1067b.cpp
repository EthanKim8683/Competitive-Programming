#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>

using namespace std;

using I=int;

const I N=1e5;

vector<pair<I,I>>adjs[N];
queue<I>que;
I viss1[N],viss2[N-1];
I degs[N];
I deps[N];
I cnts[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back({v,i});
    adjs[v].push_back({u,i});
  }
  if(n<4){printf("No\n");return 0;}
  for(I i=0;i<n;i++)
    if(adjs[i].size()==1)que.push(i);
  I cnt=n;
  while(que.size()){
    I a=que.front();que.pop();
    cnts[deps[a]]++;
    if(cnt==1&&cnts[deps[a]]!=1){printf("No\n");return 0;}
    if(cnt==1&&deps[a]!=k){printf("No\n");return 0;}
    if(deps[a]&&degs[a]<3){printf("No\n");return 0;}
    viss1[a]=2;
    cnt--;
    for(auto[b,i]:adjs[a]){
      if(viss2[i])continue;
      viss2[i]=1;
      if(viss1[b]==2){printf("No\n");return 0;}
      degs[b]++;
      if(viss1[b]==1){
        if(deps[b]!=deps[a]+1){printf("No\n");return 0;}
        continue;
      }
      viss1[b]=1;
      deps[b]=deps[a]+1;
      que.push(b);
    }
  }
  printf("Yes\n");
  return 0;
}