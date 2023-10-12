#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1000;
const I M=10000;
const Lli MAX=1e18;
pair<I,I>edgs[M];
vector<pair<I,I>>adjs[N];
Lli w_arr[M];
Lli diss1[N][N],diss2[N];
priority_queue<pair<Lli,I>>ques;
pair<I,I>pars[N];
vector<I>pats;
Lli curs[N];
void add1(I i,Lli d,I a){
  if(d>=diss1[i][a])return;
  ques.push({-(diss1[i][a]=d),a});
}
void add2(Lli d,I a,pair<I,I>p={-1,-1}){
  if(d>=diss2[a])return;
  pars[a]=p,ques.push({-(diss2[a]=d),a});
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&diss1[0][0],&diss1[0][0]+N*N,MAX);
  I n,m,l,s,t;cin>>n>>m>>l>>s>>t;
  for(I i=0;i<m;i++){
    I u,v,w;cin>>u>>v>>w;
    adjs[u].push_back({v,i});
    adjs[v].push_back({u,i});
    edgs[i]={u,v};
    w_arr[i]=w;
  }
  for(I i=0;i<n;i++){
    add1(i,0,i);
    while(ques.size()){
      auto[d,a]=ques.top();ques.pop();
      if((d=-d)!=diss1[i][a])continue;
      for(auto[b,j]:adjs[a]){
        Lli w=w_arr[j];
        if(w==0)continue;
        add1(i,d+w,b);
      }
    }
  }
  if(diss1[s][t]<l)printf("NO\n"),exit(0);
  fill_n(diss2,n,MAX);
  add2(0,s);
  while(ques.size()){
    auto[d,a]=ques.top();ques.pop();
    if((d=-d)!=diss2[a])continue;
    for(auto[b,i]:adjs[a])add2(d+max(w_arr[i],1ll),b,{a,i});
  }
  if(diss2[t]>l)printf("NO\n"),exit(0);
  Lli rem=l-diss2[t];
  I i=t;
  while(1){
    auto[j,k]=pars[i];
    if(j==-1)break;
    edgs[k]={j,i},pats.push_back(k),i=j;
  }
  reverse(pats.begin(),pats.end());
  fill_n(curs,pats.size(),MAX);
  for(I i=0;i<pats.size();i++){
    I j=pats[i];
    auto[a,b]=edgs[j];
    Lli acc=0;
    for(I k=i;k<pats.size();k++){
      I l=pats[k];
      auto[c,d]=edgs[l];
      acc-=max(w_arr[l],1ll),curs[k]=min(curs[k],diss1[a][d]+acc);
    }
    Lli con=rem;
    for(I k=i;k<pats.size();k++)con=min(con,curs[k]);
    if(w_arr[j]==0){
      w_arr[j]=con+1;
      for(I k=i;k<pats.size();k++)curs[k]-=con;
      rem-=con;
    }
  }
  printf("YES\n");
  for(I i=0;i<m;i++){
    auto[u,v]=edgs[i];
    Lli w=w_arr[i];
    printf("%i %i %lli\n",u,v,w==0?MAX:w);
  }
}
/*
first, we check if there exists a path from s to t without weight-less edges
already, and if it has weight less than L (no solution), equal to L (solution
found) or greater than L
 
if we assign all weight-less edges a weight of 1, we can find the minimum
distance from s to t having assigned all weight-less edges a positive weight
 
if the resulting distance is less than or equal to L, the remaining weight can
be distributed such that no weight exceeds the distance between both endpoints
of the edge
 
otherwise, there is no solution
*/