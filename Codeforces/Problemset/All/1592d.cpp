#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e3;
vector<I>adjs[N];
queue<I>ques;
vector<I>ords;
I pars[N];
B viss[N];
void add(I a,I p){
  if(viss[a])return;
  ords.push_back(a);
  viss[a]=1,pars[a]=p,ques.push(a);
}
I ask(I k){
  printf("? %i",k);
  for(I i=0;i<k;i++)printf(" %i",ords[i]+1);
  printf("\n"),fflush(stdout);
  I x;cin>>x;
  return x;
}
void ans(I a){
  printf("! %i %i\n",a+1,pars[a]+1),fflush(stdout);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  add(0,-1);
  while(ques.size()){
    I a=ques.front();ques.pop();
    for(auto b:adjs[a])add(b,a);
  }
  I upp=ask(n),l=2,r=n;
  while(l<r){
    I m=l+(r-l)/2;
    ask(m)==upp?r=m:l=m+1;
  }
  ans(ords[l-1]);
}
/*
since for any node w between u and v such that Dist(u, v) is maximal,
Dist(u, w) and Dist(v, w) is also maximal as Dist(u, v) describes the gcd

therefore, we can binary search for just u (or v) and answer u and a node
adjacent to it in the direction of v
*/