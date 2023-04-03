#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=200000;
pair<I,I>pnts[N];
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
B cmp(pair<I,I>a,pair<I,I>b){
  I hlf1=hlf(a),hlf2=hlf(b);
  return hlf1==hlf2?-crs(a,b)<0:hlf1<hlf2;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    pnts[i]={x,y};
  }
  sort(pnts,pnts+n,cmp);
  for(I i=0;i<n;i++){
    auto[x,y]=pnts[i];
    printf("%i %i\n",x,y);
  }
}