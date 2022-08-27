#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>

using namespace std;

using I=int;

const I N=100000;

vector<I>adjs[N];
queue<pair<I,I>>que;
I cnts[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=1;i<n;i++){I p;cin>>p,adjs[p-1].push_back(i);}
  que.push({0,0});
  I m=0;
  while(que.size()){
    auto[a,d]=que.front();que.pop();
    cnts[d]++,m=d;
    for(auto b:adjs[a])que.push({b,d+1});
  }
  I res=0;
  for(I i=0;i<=m;i++)res+=cnts[i]%2;
  printf("%i\n",res);
  return 0;
}