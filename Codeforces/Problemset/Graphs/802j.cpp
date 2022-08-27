#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;

const I N=100;
const I MAX=1e9;

vector<pair<I,I>>adjs[N];
I diss[N];
priority_queue<pair<I,I>>que;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I u,v,c;cin>>u>>v>>c;
    adjs[u].push_back({v,c});
    adjs[v].push_back({u,c});
  }
  I res=0;
  for(I i=0;i<n;i++){
    fill_n(diss,n,-MAX);
    while(que.size())que.pop();
    que.push({diss[0]=0,0});
    while(que.size()){
      auto[d,a]=que.top();que.pop();
      if(a==i){res=max(res,-d);break;}
      for(auto[b,c]:adjs[a])
        if(d-c>diss[b])que.push({diss[b]=d-c,b});
    }
  }
  printf("%i\n",res);
  return 0;
}