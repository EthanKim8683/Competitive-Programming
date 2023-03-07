#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I c_arr[N];
vector<I>adjs[N];
map<I,I>cnts[N];
pair<I,Lli>ress[N];
void dfs(I a,I p=-1){
  ress[a]={1,c_arr[a]};
  for(auto b:adjs[a])if(b!=p){
    dfs(b,a);
    if(cnts[b].size()>cnts[a].size()){
      swap(cnts[a],cnts[b]);
      ress[a]=ress[b];
    };
    for(auto[val,cnt]:cnts[b]){
      I tot=(cnts[a][val]+=cnt);
      if(tot>ress[a].first)ress[a]={tot,0};
      if(tot==ress[a].first)ress[a].second+=val;
    }
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>c_arr[i];
  for(I i=0;i<n-1;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  for(I i=0;i<n;i++)cnts[i][c_arr[i]]=1;
  dfs(0);
  for(I i=0;i<n;i++)printf("%lli ",ress[i].second);
}