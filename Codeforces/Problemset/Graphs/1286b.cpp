#include<iostream>
#include<cstdio>
#include<vector>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class Key,class Compare=less<Key>>
using indexed_set=tree<Key,null_type,Compare,rb_tree_tag,tree_order_statistics_node_update>;

using I=int;
using B=bool;

const I N=2000;

vector<I>adjs[N];
I c_arr[N];
indexed_set<I>unvs;
I ress[N];
I sums[N];

void dfs1(I a,I p=-1){
  for(auto b:adjs[a])if(b!=p){
    dfs1(b,a);
    sums[a]+=sums[b]+1;
  }
}

void dfs2(I a,I p=-1){
  auto it=unvs.find_by_order(c_arr[a]);
  ress[a]=*it;
  unvs.erase(it);
  for(auto b:adjs[a])if(b!=p)dfs2(b,a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  I r;
  for(I i=0;i<n;i++){
    I p,c;cin>>p>>c;
    c_arr[i]=c;
    if(p==0)r=i;
    else adjs[p-1].push_back(i);
  }
  for(I i=0;i<n;i++)unvs.insert(i);
  dfs1(r);
  for(I i=0;i<n;i++)
    if(c_arr[i]>sums[i]){printf("NO\n");return 0;}
  dfs2(r);
  printf("YES\n");
  for(I i=0;i<n;i++)printf("%i ",ress[i]+1);
  return 0;
}