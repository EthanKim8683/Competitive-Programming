#include<iostream>
#include<cstdio>
#include<algorithm>
#include<numeric>
#include<vector>
#include<map>
#include<queue>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

I d_arr[N];
I inds[N];
I degs[N];
vector<pair<I,I>>ress;
queue<I>viss[N];

B cmp(I a,I b){
  return d_arr[a]<d_arr[b];
}

I qry(I d){
  if(d<0||viss[d].empty())return -1;
  I res=viss[d].front();viss[d].pop();
  viss[d].push(res);
  return res;
}

void add(I d,I a){
  viss[d].push(a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>d_arr[i];
  iota(inds,inds+n,0),sort(inds,inds+n,cmp);
  I a=inds[0],d=d_arr[a];
  if(d){printf("-1\n");return 0;}
  add(d,a);
  for(I i=1;i<n;i++){
    I a=inds[i],d=d_arr[a],b=qry(d-1);
    if(b==-1){printf("-1\n");return 0;}
    add(d,a);
    degs[a]++,degs[b]++;
    ress.push_back({a,b});
  }
  for(I i=0;i<n;i++)if(degs[i]>k){printf("-1\n");return 0;}
  printf("%i\n",ress.size());
  for(auto[i,j]:ress)printf("%i %i\n",i+1,j+1);
  return 0;
}