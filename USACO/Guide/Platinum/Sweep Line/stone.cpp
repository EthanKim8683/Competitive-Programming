#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=200000;
const Lli MIN=-1e18;
pair<I,I>movs[N];
vector<tuple<pair<I,I>,I,I>>ques;
B acts[N];
I sgn(Lli i){
  return(i>0)-(i<0);
}
Lli crs(pair<I,I>a,pair<I,I>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  return (Lli)x1*y2-(Lli)y1*x2;
}
I hlf(pair<I,I>a){
  auto[x,y]=a;
  return y==0?-sgn(x):sgn(y);
}
B cmp(tuple<pair<I,I>,I,I>a,tuple<pair<I,I>,I,I>b){
  auto[mov1,t1,i1]=a;auto[mov2,t2,i2]=b;
  I hlf1=hlf(mov1),hlf2=hlf(mov2),dir=-sgn(crs(mov1,mov2));
  return hlf1==hlf2?dir==0?t1<t2:dir<0:hlf1<hlf2;
}
Lli mag(pair<I,I>a){
  auto[x,y]=a;
  return(Lli)x*x+(Lli)y*y;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    movs[i]={x,y};
    ques.push_back({{-y,x},1,i});
    ques.push_back({{y,-x},2,i});
  }
  sort(ques.begin(),ques.end(),cmp);
  for(auto[mov,t,i]:ques){
    if(t==1)acts[i]=1;
    if(t==2)acts[i]^=1;
  }
  I x1=0,y1=0;
  for(I i=0;i<n;i++)if(acts[i]){
    auto[x2,y2]=movs[i];
    x1+=x2,y1+=y2;
  }
  Lli res=MIN;
  for(auto[mov,t,i]:ques){
    auto[x2,y2]=movs[i];
    if(t==1)x1+=x2,y1+=y2;
    if(t==2)x1-=x2,y1-=y2;
    res=max(res,mag({x1,y1}));
  }
  printf("%lli\n",res);
}