#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I M=2e5;
const I MIN=-1e9;
pair<I,I>edgs[M];
vector<pair<I,I>>adjs[N];
queue<I>ques;
I cnts[N];
B viss1[N],viss2[M];
vector<I>curs;
I ress[M];
I k;
I cnt;
void chk(I a){
  if(viss1[a]||cnts[a]>=k)return;
  cnt--,viss1[a]=1,ques.push(a);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m>>k;
  for(I i=0;i<m;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back({y,i});
    adjs[y].push_back({x,i});
    edgs[i]={x,y};
  }
  cnt=n;
  for(I i=0;i<n;i++)cnts[i]=adjs[i].size(),chk(i);
  for(I i=m-1;i>=0;i--){
    while(ques.size()){
      I a=ques.front();ques.pop();
      for(auto[b,j]:adjs[a])if(!viss2[j])cnts[b]--,viss2[j]=1,chk(b);
    }
    ress[i]=cnt;
    if(!viss2[i]){
      viss2[i]=1;
      auto[x,y]=edgs[i];
      cnts[x]--,cnts[y]--,chk(x),chk(y);
    }
  }
  for(I i=0;i<m;i++)printf("%i\n",ress[i]);
}