#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

vector<I>adjs[N];
vector<pair<I,I>>edgs;
vector<I>rgts,lfts,mids;
B viss[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,h,t;cin>>n>>m>>h>>t;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
    edgs.push_back({a,b});
    edgs.push_back({b,a});
  }
  I c=-1,d=-1;
  for(auto[a,b]:edgs){
    if(adjs[a].size()-1<h)continue;
    if(adjs[b].size()-1<t)continue;
    if(adjs[a].size()-1+adjs[b].size()-1<h+t)continue;
    if(adjs[a].size()-1>=h+t){c=a,d=b;break;}
    if(adjs[b].size()-1>=h+t){c=a,d=b;break;}
    I cnt=0;
    for(auto i:adjs[a])if(i!=a&&i!=b)viss[i]=1,cnt++;
    for(auto i:adjs[b])if(i!=a&&i!=b)cnt+=!viss[i];
    for(auto i:adjs[a])if(i!=a&&i!=b)viss[i]=0;
    if(cnt>=h+t){c=a,d=b;break;}
  }
  if(c==-1&&d==-1)printf("NO\n"),exit(0);
  sort(adjs[c].begin(),adjs[c].end());
  sort(adjs[d].begin(),adjs[d].end());
  for(I i=0;i<n;i++){
    if(i==c||i==d)continue;
    I vis1=binary_search(adjs[c].begin(),adjs[c].end(),i);
    I vis2=binary_search(adjs[d].begin(),adjs[d].end(),i);
    if(vis1&&vis2)mids.push_back(i);
    else if(vis1)lfts.push_back(i);
    else if(vis2)rgts.push_back(i);
  }
  while(mids.size()&&(lfts.size()<h||rgts.size()<t)){
    I a=mids.back();mids.pop_back();
    if(lfts.size()<h){lfts.push_back(a);continue;}
    if(rgts.size()<t){rgts.push_back(a);continue;}
  }
  printf("YES\n");
  printf("%i %i\n",c+1,d+1);
  for(I i=0;i<h;i++)printf("%i ",lfts[i]+1);
  printf("\n");
  for(I i=0;i<t;i++)printf("%i ",rgts[i]+1);
}