#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lf=long double;
const I N=100000;
tuple<I,I,I,I>hils[N];
priority_queue<tuple<I,I,I>>ques;
I x=0;
Lf evl(I a){
  auto[x1,y1,x2,y2]=hils[a];
  return(Lf)(x-x1)/(x2-x1)*(y2-y1)+y1;
}
B cmp(I a,I b){
  return evl(a)<evl(b);
}
set<I,decltype(cmp)*>curs(cmp);
I main(){
  cin.tie(0)->sync_with_stdio(0);
#ifndef ETHANKIM8683
  freopen("hillwalk.in","r",stdin);
  freopen("hillwalk.out","w",stdout);
#endif
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
    hils[i]={x1,y1,x2,y2};
    ques.push({-x1,2,i});
    ques.push({-x2,1,i});
  }
  I j=0,res=1;
  while(ques.size()){
    auto[cur,t,i]=ques.top();ques.pop();
    x=-cur;
    if(t==2)curs.insert(i);
    if(t==1){
      if(i==j){
        while(1){
          auto it=curs.upper_bound(j);
          if(it==curs.begin())break;
          I k=*prev(it);
          if(get<2>(hils[k])!=x)break;
          curs.erase(k);
        }
        auto it=curs.lower_bound(j);
        if(it==curs.begin())break;
        j=*prev(it),res++;
      }
      if(curs.count(i))curs.erase(i);
    }
  }
  printf("%i\n",res);
}