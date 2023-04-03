#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
using Lf=float;
const I N=500000;
const I R=30000;
vector<pair<I,I>>pnts[R];
vector<tuple<pair<I,I>,I,I>>ques;
pair<I,I>poss[4*N];
B acts[R];
I x,y;
Lli crs(pair<I,I>a,pair<I,I>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  return(Lli)x1*y2-(Lli)y1*x2;
}
I sgn(I i){
  return(i>0)-(i<0);
}
I hlf(pair<I,I>a){
  auto[x,y]=a;
  return y==0?-sgn(x):sgn(y);
}
Lli dif(pair<I,I>a,pair<I,I>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  x1-=x,y1-=y,x2-=x,y2-=y;
  I hlf1=hlf({x1,y1}),hlf2=hlf({x2,y2});
  return hlf1==hlf2?-crs({x1,y1},{x2,y2}):hlf1-hlf2;
}
B cmp1(pair<I,I>a,pair<I,I>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  x1-=x,y1-=y,x2-=x,y2-=y;
  return-crs({x1,y1},{x2,y2})<0;
}
B cmp2(tuple<pair<I,I>,I,I>a,tuple<pair<I,I>,I,I>b){
  auto[pos1,t1,i1]=a;auto[pos2,t2,i2]=b;
  Lli res=dif(pos1,pos2);
  return res==0?t1<t2:res<0;
}
B cmp3(pair<I,I>a,pair<I,I>b){
  return dif(a,b)<0;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,r;cin>>n>>r;
  cin>>x>>y;
  for(I i=0;i<r;i++){
    I p;cin>>p;
    for(I j=0;j<p;j++){
      I x,y;cin>>x>>y;
      pnts[i].push_back({x,y});
    }
    sort(pnts[i].begin(),pnts[i].end(),cmp1);
    ques.push_back({pnts[i].front(),1,i});
    ques.push_back({pnts[i].back(),2,i});
  }
  for(I i=0;i<n;i++){
    poss[i]={i,n};
    poss[i+n]={n,n-i};
    poss[i+2*n]={n-i,0};
    poss[i+3*n]={0,i};
  }
  sort(ques.begin(),ques.end(),cmp2);
  sort(poss,poss+4*n,cmp3);
  for(auto[pos,t,i]:ques){
    auto[x,y]=pos;
    if(t==1)acts[i]=1;
    if(t==2)acts[i]^=1;
  }
  I res=0,cur=accumulate(acts,acts+r,0),j=0;
  for(auto[pos,t,i]:ques){
    while(j<4*n){
      Lli ang=dif(poss[j],pos);
      if(ang>0||(ang==0&&t==1))break;
      res+=!cur,j++;
    }
    if(t==1)cur++;
    if(t==2)cur--;
  }
  if(!cur)res+=4*n-j;
  printf("%i\n",res);
}