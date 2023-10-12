#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
const I N=1e5;
map<S,I>lows;
vector<I>inds;
vector<I>adjs[N];
vector<I>tops;
B viss[N];
void dfs(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto b:adjs[a])dfs(b);
  tops.push_back(a);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  for(I i=0;i<n;i++){
    S s;cin>>s;
    lows[s]=i;
  }
  for(I i=0;i<m;i++){
    S s;I t;cin>>s>>t,t--;
    inds.clear();
    for(I j=0;j<(1<<k);j++){
      S u=s;
      for(I l=0;l<k;l++)if(j>>l&1)u[l]='_';
      auto it=lows.find(u);
      if(it!=lows.end())inds.push_back(it->second);
    }
    B fnd=0;
    for(auto b:inds){
      if(b==t){fnd=1;continue;}
      adjs[t].push_back(b);
    }
    if(!fnd)printf("NO\n"),exit(0);
  }
  for(I i=0;i<n;i++)dfs(i);
  reverse(tops.begin(),tops.end());
  fill_n(viss,n,0);
  for(auto i:tops){
    for(auto j:adjs[i])if(viss[j])printf("NO\n"),exit(0);
    viss[i]=1;
  }
  printf("YES\n");
  for(auto i:tops)printf("%i ",i+1);
}