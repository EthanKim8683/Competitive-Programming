#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;

/*
Count for each node is the number of first nodes
in a path where a farmer's distance is lower than
Bessie's distance to that node.

Think of, like, a shifting blob of nodes where
each node's distance to Bessie is less than its
distance to a farmer, and the number of nodes
immediately around the blob is the count of the
node (far<=bes).

Thus, for each node, create a "radius" of nodes
where the current node would be an perimeter node.
*/

const I N=7e4;
const I MAX=1e9;

vector<I>adjs[N];
queue<pair<I,I>>que;
I diss[N];
I deps[N];
I dep=0;

void dfs1(I a,I p=-1){
  deps[a]=dep;
  dep++;
  for(auto b:adjs[a]){
    if(b==p)continue;
    dfs1(b,a);
  }
  dep--;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  fill_n(diss,n,MAX);
  for(I i=0;i<n;i++)
    if(adjs[i].size()==1)
      que.push({diss[i]=0,i});
  while(que.size()){
    auto[dis,a]=que.front();
    que.pop();
    for(auto b:adjs[a])
      if(dis+1<diss[b])
        que.push({diss[b]=dis+1,b});
  }
  for(I i=0;i<n;i++)
    printf("%i ",diss[i]);
  printf("\n\n");
  for(I i=0;i<n;i++){
    dfs1(i);
    for(I j=0;j<n;j++)
      printf("%i ",deps[j]-diss[j]);
    printf("\n");
  }
  return 0;
}