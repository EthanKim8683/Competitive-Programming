#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
using Lf=long double;
const Lf MAX=1e99L;
pair<Lf,Lf>operator-(pair<Lf,Lf>a,pair<Lf,Lf>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  return{x1-x2,y1-y2};
}
pair<Lf,Lf>operator*(Lf a,pair<Lf,Lf>b){
  auto[x,y]=b;
  return{a*x,a*y};
}
I sgn(Lli x){
  return(x>0)-(x<0);
}
Lli crs(pair<I,I>a,pair<I,I>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  return(Lli)x1*y2-(Lli)y1*x2;
}
Lli crs(pair<I,I>a,pair<I,I>b,pair<I,I>c){
  auto[x1,y1]=a;auto[x2,y2]=b;auto[x3,y3]=c;
  return(Lli)(x2-x1)*(y3-y2)-(Lli)(y2-y1)*(x3-x2);
}
Lf dot(pair<Lf,Lf>a,pair<Lf,Lf>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  return x1*x2+y1*y2;
}
B ict(pair<pair<I,I>,pair<I,I>>u,pair<pair<I,I>,pair<I,I>>v){
  auto[a1,b1]=u;auto[a2,b2]=v;
  if(crs(a1-b1,a2-b2)==0)return 0;
  I sgn1=sgn(crs(a1,a2,b1))*sgn(crs(a1,b2,b1));
  I sgn2=sgn(crs(a2,a1,b2))*sgn(crs(a2,b1,b2));
  return sgn1<=0&&sgn2<=0;
}
Lf len(pair<Lf,Lf>a){
  return sqrt(dot(a,a));
}
Lf dis(pair<pair<I,I>,pair<I,I>>u,pair<I,I>c){
  auto[a,b]=u;
  if(a==b)return len(a-c);
  auto ba=b-a,ca=c-a;
  Lf h=clamp((Lf)dot(ca,ba)/dot(ba,ba),0.L,1.L);
  return len(ca-h*ba);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x1,y1,x2,y2,x3,y3,x4,y4;cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
    Lf res=MAX;
    if(ict({{x1,y1},{x2,y2}},{{x3,y3},{x4,y4}}))res=0;
    res=min(res,dis({{x1,y1},{x2,y2}},{x3,y3}));
    res=min(res,dis({{x1,y1},{x2,y2}},{x4,y4}));
    res=min(res,dis({{x3,y3},{x4,y4}},{x1,y1}));
    res=min(res,dis({{x3,y3},{x4,y4}},{x2,y2}));
    printf("%.2Lf\n",res);
  }
}