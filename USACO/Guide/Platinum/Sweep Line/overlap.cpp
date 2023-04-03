#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=50000;
const I MAX=1e9;
const I MIN=-MAX;
pair<I,I>poss[N];
priority_queue<tuple<I,I,I>>ques;
set<pair<I,I>>curs;
set<pair<I,I>>viss;
I k;
Lli olp(I a,I b){
  auto[x1,y1]=poss[a];auto[x2,y2]=poss[b];
  if(x1>x2)swap(x1,x2),swap(y1,y2);
  return(Lli)(k-x2+x1)*(min(y1,y2)-max(y1,y2)+k);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
#ifndef ETHANKIM8683
  freopen("squares.in","r",stdin);
  freopen("squares.out","w",stdout);
#endif
  I n;cin>>n>>k;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    poss[i]={x,y};
    ques.push({-x,1,i}),ques.push({-x-k+1,2,i});
  }
  Lli res=0;
  while(ques.size()&&res!=-1){
    auto[x,t,i]=ques.top();ques.pop();
    I y=poss[i].second;
    if(t==1){
      auto low=curs.lower_bound({y,MIN});
      auto upp=curs.upper_bound({y+k-1,MAX});
      for(auto it=low;it!=upp;it++){
        I j=it->second;
        if(viss.count({i,j}))continue;
        viss.insert({i,j});
        if(res!=0){res=-1;continue;}
        res=olp(i,j);
      }
      curs.insert({y,i}),curs.insert({y+k-1,i});
    }
    if(t==2){
      curs.erase({y,i}),curs.erase({y+k-1,i});
    }
  }
  printf("%lli\n",res);
}