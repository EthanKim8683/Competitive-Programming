#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
using B=bool;
const I N=1e5;
const I CNT=128;
const Lf RAD=1e15;
const Lf MAX=1e300;
const Lf MIN=-MAX;
pair<Lf,Lf>lars[N];
I n;
B chk(Lf rad){
  Lf upp=MAX,low=MIN;
  for(I i=0;i<n;i++){
    auto[x,y]=lars[i];
    if(y>2*rad)return 0;
    Lf dis=sqrt(2*y*rad-y*y);
    upp=min(upp,x+dis),low=max(low,x-dis);
  }
  return low<=upp;
}
Lf fnd(){
  Lf l=0,r=RAD;
  for(I i=0;i<CNT;i++){
    Lf m=(l+r)/2;
    chk(m)?r=m:l=m;
  }
  return(l+r)/2;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  I sgn=0;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    if(sgn==0)sgn=y>0;
    if((y>0)!=sgn)printf("-1"),exit(0);
    lars[i]={x,abs(y)};
  }
  printf("%.10Lf\n",fnd());
}