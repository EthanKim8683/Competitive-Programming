#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=1500;
pair<I,I>pnts[N];
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
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    pnts[i]={x,y};
  }
}