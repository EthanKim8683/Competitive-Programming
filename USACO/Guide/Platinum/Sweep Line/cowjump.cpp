#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
using Lf=long double;
const I N=1e5;
pair<I,I>pnts[2*N];
pair<I,I>edgs[N];
priority_queue<tuple<I,I,I>>ques;
I x=0;
I sid(I a,I b,I c){
  auto[x1,y1]=pnts[a];auto[x2,y2]=pnts[b];auto[x3,y3]=pnts[c];
  Lli x5=x3-x1,y5=y3-y1,x6=x3-x2,y6=y3-y2,crs=x5*y6-x6*y5;
  return(crs>0)-(crs<0);
}
B ict(I a,I b){
  I sid1=sid(a*2,a*2+1,b*2)*sid(a*2,a*2+1,b*2+1);
  I sid2=sid(b*2,b*2+1,a*2)*sid(b*2,b*2+1,a*2+1);
  return sid1<=0&&sid2<=0;
}
Lf evl(I a){
  auto[x1,y1]=pnts[a*2];auto[x2,y2]=pnts[a*2+1];
  return(Lf)(x-x1)/(x2-x1)*(y2-y1)+y1;
}
B cmp(I a,I b){
  Lf y1=evl(a),y2=evl(b);
  return y1==y2?a<b:y1<y2;
}
set<I,decltype(cmp)*>curs(cmp);
I main(){
  cin.tie(0)->sync_with_stdio(0);
#ifndef ETHANKIM8683
  freopen("cowjump.in","r",stdin);
  freopen("cowjump.out","w",stdout);
#endif
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
    pnts[i*2]={x1,y1},pnts[i*2+1]={x2,y2};
    if(x1==x2){
      ques.push({-x1,2,i});
    }else{
      ques.push({-x1,3,i}),ques.push({-x2,1,i});
    }
  }
  I res1=-1,res2=-1;
  while(ques.size()){
    auto[cur,t,i]=ques.top();ques.pop();
    x=-cur;
    if(t==3){
      curs.insert(i);
      auto low=curs.lower_bound(i);
      auto upp=curs.upper_bound(i);
      if(low!=curs.begin()){
        I j=*prev(low);
        if(ict(j,i)){res1=j,res2=i;break;}
      }
      if(upp!=curs.end()){
        I j=*upp;
        if(ict(i,j)){res1=i,res2=j;break;}
      }
    }
    if(t==1){
      curs.erase(i);
      auto low=curs.lower_bound(i);
      auto upp=curs.upper_bound(i);
      if(low!=curs.begin()&&upp!=curs.end()){
        I j=*prev(low),k=*upp;
        if(ict(j,k)){res1=j,res2=k;break;}
      }
    }
    if(t==2){
      if(curs.size()){
        auto it=curs.begin();I j;
        while(it!=curs.end()&&!ict(j=*it++,i));
        if(ict(i,j)){res1=i,res2=j;break;}
      }
    }
  }
  if(res1>res2)swap(res1,res2);
  I cnt=0;
  for(I i=0;i<n;i++)if(i!=res2)cnt+=ict(i,res2);
  printf("%i\n",(cnt>1?res2:res1)+1);
}