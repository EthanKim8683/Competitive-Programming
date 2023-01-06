#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
Lli r,g,b;
B chk1(Lli x){
  Lli y=(r-x)/2;
  return y+2*x<=g+b;
}
Lli fnd1(){
  Lli l=0,u=r;
  while(l<u){
    Lli m=l+(u-l+1)/2;
    chk1(m)?l=m:u=m-1;
  }
  return l;
}
B chk2(Lli x){
  Lli y=(g-x)/2;
  return y+2*x<=b;
}
Lli fnd2(){
  Lli l=0,u=g;
  while(l<u){
    Lli m=l+(u-l+1)/2;
    chk2(m)?l=m:u=m-1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>r>>g>>b;
  if(r>g)swap(r,g);
  if(r>b)swap(r,b);
  if(g>b)swap(g,b);
  Lli x=fnd1(),y=(r-x)/2;
  r-=2*y+x;
  Lli rem=y+2*x,dif=min(rem,b-g);
  rem-=dif,b-=dif;
  g-=rem/2,b-=rem/2,rem-=rem/2*2;
  g-=rem;
  Lli z=fnd2(),w=(g-z)/2;
  g-=2*w+z;
  b-=w+2*z;
  printf("%lli\n",x+y+z+w);
}