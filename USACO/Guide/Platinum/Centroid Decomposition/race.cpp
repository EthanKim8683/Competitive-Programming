#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=200000;
const I MAX=1e9;
vector<pair<I,I>>adjs[N];
I sizs[N];
B viss[N];
map<Lli,I>diss;
I res=MAX;
I k;
I dfs1(I a,I p=-1){
  sizs[a]=1;
  for(auto[b,w]:adjs[a])if(b!=p&&!viss[b])sizs[a]+=dfs1(b,a);
  return sizs[a];
}
I dfs2(I a,I siz,I p=-1){
  for(auto[b,w]:adjs[a])if(b!=p&&!viss[b]&&sizs[b]*2>siz)return dfs2(b,siz,a);
  return a;
}
void dfs4(I a,I p,Lli d,I l){
  if(diss.count(k-d))res=min(res,diss[k-d]+l);
  for(auto[b,w]:adjs[a])if(b!=p&&!viss[b])dfs4(b,a,d+w,l+1);
}
void dfs5(I a,I p,Lli d,I l){
  if(!diss.count(d))diss[d]=MAX;
  diss[d]=min(diss[d],l);
  for(auto[b,w]:adjs[a])if(b!=p&&!viss[b])dfs5(b,a,d+w,l+1);
}
void dfs3(I a){
  a=dfs2(a,dfs1(a));
  viss[a]=1;
  diss.clear();
  diss[0]=0;
  for(auto[b,w]:adjs[a])if(!viss[b])dfs4(b,a,w,1),dfs5(b,a,w,1);
  for(auto[b,w]:adjs[a])if(!viss[b])dfs3(b);
}
I best_path(I n,I t,I h_arr[][2],I l_arr[]){
  k=t;
  for(I i=0;i<n-1;i++){
    I a=h_arr[i][0],b=h_arr[i][1],l=l_arr[i];
    adjs[a].push_back({b,l});
    adjs[b].push_back({a,l});
  }
  dfs3(0);
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