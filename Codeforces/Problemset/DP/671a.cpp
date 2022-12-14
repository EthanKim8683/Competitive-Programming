#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I N=100000;
const Lf MAX=1e300;
pair<I,I>bots[N];
Lf csts1[N],csts2[N];
multiset<Lf>vals;
Lf dis(I x1,I y1,I x2,I y2){
  Lf dx=x1-x2,dy=y1-y2;
  return sqrt(dx*dx+dy*dy);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I ax,ay,bx,by,tx,ty;cin>>ax>>ay>>bx>>by>>tx>>ty;
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    bots[i]={x,y};
  }
  Lf res=MAX;
  if(n==1){
    auto[x,y]=bots[0];
    Lf d1=dis(x,y,tx,ty);
    res=min(res,dis(x,y,ax,ay)+d1);
    res=min(res,dis(x,y,bx,by)+d1);
    printf("%.12Lf\n",res);
    exit(0);
  }
  Lf cur=0;
  for(I i=0;i<n;i++){
    auto[x,y]=bots[i];
    Lf d1=dis(x,y,tx,ty);
    csts1[i]=dis(x,y,ax,ay)-d1;
    csts2[i]=dis(x,y,bx,by)-d1;
    cur+=2*d1;
  }
  for(I i=0;i<n;i++)vals.insert(csts1[i]);
  for(I i=0;i<n;i++){
    vals.erase(vals.find(csts1[i]));
    res=min(res,cur+*vals.begin()+csts2[i]);
    vals.insert(csts1[i]);
  }
  res=min(res,cur+*min_element(csts1,csts1+n));
  res=min(res,cur+*min_element(csts2,csts2+n));
  printf("%.12Lf\n",res);
}