#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;
const I K=N;
const I MAX=1e9;

I a_arr[K];
vector<I>adjs[N];
I diss1[N],diss2[N];
queue<I>que1,que2;
set<pair<I,I>>unvs1,unvs2;

void add1(I d,I a){
  if(d>=diss1[a])return;
  diss1[a]=d,que1.push(a);
}

void add2(I d,I a){
  if(d>=diss2[a])return;
  diss2[a]=d,que2.push(a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  fill_n(diss1,n,MAX);
  fill_n(diss2,n,MAX);
  for(I i=0;i<k;i++){I a;cin>>a,a_arr[i]=a-1;}
  for(I i=0;i<m;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  add1(0,0);
  while(que1.size()){
    I a=que1.front();que1.pop();
    for(auto b:adjs[a])add1(diss1[a]+1,b);
  }
  add2(0,n-1);
  while(que2.size()){
    I a=que2.front();que2.pop();
    for(auto b:adjs[a])add2(diss2[a]+1,b);
  }
  for(I i=0;i<k;i++){
    I a=a_arr[i];
    unvs1.insert({diss1[a],a});
    unvs2.insert({diss2[a],a});
  }
  I res=0;
  for(I i=0;i<k;i++){
    I a=a_arr[i];
    unvs1.erase({diss1[a],a});
    unvs2.erase({diss2[a],a});
    auto it1=unvs1.lower_bound({diss1[a],0});
    auto it2=unvs2.lower_bound({diss2[a],0});
    if(it1!=unvs1.end())res=max(res,diss1[a]+diss2[it1->second]+1);
    if(it2!=unvs2.end())res=max(res,diss2[a]+diss1[it2->second]+1);
    unvs1.insert({diss1[a],a});
    unvs2.insert({diss2[a],a});
  }
  printf("%i\n",min(diss1[n-1],res));
}