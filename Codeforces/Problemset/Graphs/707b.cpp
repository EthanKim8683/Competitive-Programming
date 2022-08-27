#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I MAX=1e9+1;

vector<pair<I,I>>adjs[N];
queue<I>que;
I diss[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  fill_n(diss,n,MAX);
  for(I i=0;i<m;i++){
    I u,v,l;cin>>u>>v>>l,u--,v--;
    adjs[u].push_back({v,l});
    adjs[v].push_back({u,l});
  }
  for(I i=0;i<k;i++){
    I a;cin>>a,a--;
    diss[a]=0;
    que.push(a);
  }
  I res=MAX;
  while(que.size()){
    I a=que.front();
    que.pop();
    for(auto[b,d]:adjs[a]){
      if(d>=diss[b])continue;
      diss[b]=d;
      res=min(res,d);
    }
  }
  printf("%i\n",res!=MAX?res:-1);
  return 0;
}