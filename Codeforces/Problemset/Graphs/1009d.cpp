#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

B nrps[N];
vector<pair<I,I>>ress;
I degs[N+1];
priority_queue<pair<I,I>>que;

I gcd(I a,I b){
  while(b)a%=b,swap(a,b);
  return a;
}

void add(I i,I j){
  que.push({-++degs[i],i}),que.push({-++degs[j],j});
  ress.push_back({i,j});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=1;i<=n&&ress.size()<m;i++){
    if(i!=1)ress.push_back({1,i});
    que.push({-++degs[i],i}),degs[1]++;
  }
  while(ress.size()<m&&que.size()){
    auto[d,i]=que.top();que.pop();
    if((d*=-1)!=degs[i])continue;
    for(I j=2;j<i&&ress.size()<m;j++)
      if(gcd(i,j)==1)ress.push_back({i,j});
  }
  if(ress.size()<m||m<n-1){printf("Impossible");return 0;}
  printf("Possible\n");
  for(auto[i,j]:ress)printf("%i %i\n",i,j);
  return 0;
}