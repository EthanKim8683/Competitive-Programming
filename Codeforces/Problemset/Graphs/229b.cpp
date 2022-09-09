#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;

const I N=1e5;
const I MAX=2e9;

vector<pair<I,I>>adjs[N];
vector<pair<I,I>>trvs[N];
priority_queue<pair<I,I>>que;
I diss[N];
I n;

void add(I i,I d){
  if(i!=n-1){
    auto low=lower_bound(trvs[i].begin(),trvs[i].end(),pair<I,I>{d,0});
    auto upp=upper_bound(trvs[i].begin(),trvs[i].end(),pair<I,I>{d,MAX});
    if(low!=upp)d=low->second;
  }
  if(d>=diss[i])return;
  que.push({-(diss[i]=d),i});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  fill_n(diss,n,MAX);
  for(I i=0;i<m;i++){
    I a,b,c;cin>>a>>b>>c,a--,b--;
    adjs[a].push_back({b,c}),adjs[b].push_back({a,c});
  }
  for(I i=0;i<n;i++){
    I k;cin>>k;
    for(I j=0;j<k;j++){I t;cin>>t;trvs[i].push_back({t,t+1});}
    sort(trvs[i].begin(),trvs[i].end());
    for(I j=k-2;j>=0;j--)if(trvs[i][j].first+1==trvs[i][j+1].first)
      trvs[i][j].second=trvs[i][j+1].second;
  }
  add(0,0);
  while(que.size()){
    auto[d,a]=que.top();que.pop();
    if((d*=-1)!=diss[a])continue;
    for(auto[b,c]:adjs[a])add(b,d+c);
  }
  if(diss[n-1]==MAX)printf("-1\n");
  else printf("%i\n",diss[n-1]);
  return 0;
}