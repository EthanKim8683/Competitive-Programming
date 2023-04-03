#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
using B=bool;
const I N=500;
const I X=10000;
const I Y=10000;
const I ITR1=15;
const I ITR2=60;
const Lf MAX=sqrt(X*X+Y*Y)/2;
pair<I,I>pnts[N];
Lf diss[N][N];
vector<tuple<pair<Lf,Lf>,I,I>>ques;
B acts[N];
pair<Lf,I>res={MAX,-1};
I n,k;
Lf crs(pair<Lf,Lf>a,pair<Lf,Lf>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  return x1*y2-y1*x2;
}
I sgn(Lf i){
  return(i>0)-(i<0);
}
I hlf(pair<Lf,Lf>a){
  auto[x,y]=a;
  return y==0?-sgn(x):sgn(y);
}
Lf dif(pair<Lf,Lf>a,pair<Lf,Lf>b){
  I hlf1=hlf(a),hlf2=hlf(b);
  return hlf1==hlf2?-crs(a,b):hlf1-hlf2;
}
B cmp(tuple<pair<Lf,Lf>,I,I>a,tuple<pair<Lf,Lf>,I,I>b){
  auto[pos1,t1,i1]=a;auto[pos2,t2,i2]=b;
  Lf res=dif(pos1,pos2);
  return res==0?t1<t2:res<0;
}
Lf dis(I a,I b){
  auto[x1,y1]=pnts[a];auto[x2,y2]=pnts[b];
  Lf dx=x1-x2,dy=y1-y2;
  return sqrt(dx*dx+dy*dy);
}
pair<Lf,Lf>slv(I i,Lf r){
  ques.clear();
  for(I j=0;j<n;j++)if(j!=i){
    Lf d=diss[i][j];
    if(d>2*r)continue;
    auto[x1,y1]=pnts[i];auto[x2,y2]=pnts[j];
    Lf dx=x2-x1,dy=y2-y1,x3=dx/2,y3=dy/2,f=sqrt(r*r-d*d/4)/d;
    dx*=f,dy*=f;
    ques.push_back({{x3+dy,y3-dx},1,j});
    ques.push_back({{x3-dy,y3+dx},2,j});
  }
  if(ques.size()<(k-1)*2)return{-1,-1};
  sort(ques.begin(),ques.end(),cmp);
  fill_n(acts,n,0);
  for(auto[pos,t,j]:ques){
    if(t==1)acts[j]=1;
    if(t==2)acts[j]^=1;
  }
  I cur=accumulate(acts,acts+n,0);
  for(auto[pos,t,j]:ques){
    if(t==1)cur++;
    if(t==2)cur--;
    if(cur>=k-1){
      auto[x1,y1]=pnts[i];auto[x2,y2]=pos;
      return{x1+x2,y1+y2};
    };
  }
  return{-1,-1};
}
B chk(I i,Lf r){
  return slv(i,r)!=pair<Lf,Lf>{-1,-1};
}
Lf fnd1(I i){
  Lf l=0,r=res.first;
  for(I j=0;j<ITR1;j++){
    Lf m=(l+r)/2;
    chk(i,m)?r=m:l=m;
  }
  return r;
}
Lf fnd2(I i){
  Lf l=0,r=res.first;
  for(I j=0;j<ITR2;j++){
    Lf m=(l+r)/2;
    chk(i,m)?r=m:l=m;
  }
  return r;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>k;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    pnts[i]={x,y};
  }
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)diss[i][j]=dis(i,j);
  for(I i=0;i<n;i++)res=min(res,{fnd1(i),i});
  auto[r,i]=res;
  auto[x,y]=slv(i,r=fnd2(i));
  printf("%.6Lf\n",r);
  printf("%.6Lf %.6Lf\n",x,y);
}