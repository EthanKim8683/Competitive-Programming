#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;
const Lli MAX=1e18;

vector<pair<I,I>>adjs[N];
I pars[N];
Lli diss[N];
priority_queue<pair<Lli,I>>que;
vector<I>ress;

void add(Lli d,I a,I p=-1){
  if(d>=diss[a])return;
  que.push({-(diss[a]=d),a}),pars[a]=p;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(diss,n,MAX);
  for(I i=0;i<m;i++){
    I a,b,w;cin>>a>>b>>w,a--,b--;
    adjs[a].push_back({b,w});
    adjs[b].push_back({a,w});
  }
  add(0,0);
  while(que.size()){
    auto[d,a]=que.top();que.pop();
    if((d=-d)!=diss[a])continue;
    for(auto[b,w]:adjs[a])add(d+w,b,a);
  }
  if(diss[n-1]==MAX){printf("-1\n");return 0;}
  I a=n-1;
  while(a!=-1)ress.push_back(a),a=pars[a];
  reverse(ress.begin(),ress.end());
  for(auto i:ress)printf("%i ",i+1);
  return 0;
}