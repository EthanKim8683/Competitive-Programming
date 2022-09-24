#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<tuple>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=3e5;
const I M=3e5;

vector<I>adjs1[N];
vector<tuple<I,I,B>>adjs2[N];
queue<I>que;
B viss[N];
B ress1[M],ress2[M];

B add(I i){
  if(viss[i])return 0;
  que.push(i),viss[i]=1;
  return 1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,s;cin>>n>>m>>s,s--;
  I len=0;
  for(I i=0;i<m;i++){
    I t,u,v;cin>>t>>u>>v,u--,v--;
    if(t==1)adjs1[u].push_back(v);
    if(t==2){
      adjs2[u].push_back({v,len,1});
      adjs2[v].push_back({u,len,0});
      len++;
    }
  }
  I res1=0,res2=0;
  add(s);
  while(que.size()){
    I a=que.front();que.pop();
    for(auto b:adjs1[a])add(b);
    for(auto[b,i,d]:adjs2[a])if(add(b))ress1[i]=d;
    res1++;
  }
  fill_n(viss,n,0);
  add(s);
  while(que.size()){
    I a=que.front();que.pop();
    for(auto b:adjs1[a])add(b);
    for(auto[b,i,d]:adjs2[a])ress2[i]=!d;
    res2++;
  }
  printf("%i\n",res1);
  for(I i=0;i<len;i++)printf("%c",ress1[i]?'+':'-');
  printf("\n%i\n",res2);
  for(I i=0;i<len;i++)printf("%c",ress2[i]?'+':'-');
  return 0;
}