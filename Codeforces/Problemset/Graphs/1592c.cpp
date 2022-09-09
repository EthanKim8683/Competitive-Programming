#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

I a_arr[N];
vector<I>adjs[N];
I xors[N];
I cnts[N];
I val;

void dfs(I a,I p=-1){
  xors[a]=a_arr[a];
  cnts[a]=0;
  for(auto b:adjs[a]){
    if(b==p)continue;
    dfs(b,a);
    if(xors[b]!=val)xors[a]^=xors[b];
    else cnts[a]++;
    cnts[a]+=cnts[b];
  }
  if(xors[a]==0&&cnts[a])xors[a]=val,cnts[a]--;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<n-1;i++){
      I u,v;cin>>u>>v,u--,v--;
      adjs[u].push_back(v);
      adjs[v].push_back(u);
    }
    val=0;
    for(I i=0;i<n;i++)val^=a_arr[i];
    if(val==0){printf("YES\n");continue;}
    dfs(0);
    if(xors[0]==val&&cnts[0]&&2<k)printf("YES\n");
    else printf("NO\n");
  }
  return 0;
}