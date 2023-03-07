#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200000;
const I MAX=1e9;
vector<pair<I,I>>adjs[N];
map<Lli,I>vals[N];
I res=MAX;
I len;
void dfs(I a,I p=-1,I dep1=0,Lli dis1=0){
  vals[a][dis1]=dep1;
  for(auto[b,l]:adjs[a])if(b!=p){
    dfs(b,a,dep1+1,dis1+l);
    if(vals[b].size()>vals[a].size())swap(vals[a],vals[b]);
    for(auto[dis2,dep2]:vals[b]){
      Lli dis3=len-(dis2-dis1)+dis1;
      if(!vals[a].count(dis3))continue;
      res=min(res,vals[a][dis3]+dep2-dep1*2);
    }
    for(auto[dis2,dep2]:vals[b]){
      if(!vals[a].count(dis2))vals[a][dis2]=MAX;
      vals[a][dis2]=min(vals[a][dis2],dep2);
    }
  }
}
I best_path(I n,I k,I h_arr[][2],I l_arr[]){
  len=k;
  for(I i=0;i<n-1;i++){
    I a=h_arr[i][0],b=h_arr[i][1],l=l_arr[i];
    adjs[a].push_back({b,l});
    adjs[b].push_back({a,l});
  }
  dfs(0);
  return res==MAX?-1:res;
}
#ifdef ETHANKIM8683
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  I h_arr[n-1][2],l_arr[n-1];
  for(I i=0;i<n;i++)cin>>h_arr[i][0]>>h_arr[i][1]>>l_arr[i];
  printf("%i\n",best_path(n,k,h_arr,l_arr));
}
#endif