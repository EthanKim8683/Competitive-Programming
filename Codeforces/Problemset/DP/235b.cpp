#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I N=1e5;
Lf p_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>p_arr[i];
  Lf x0=0,v0=0,a0=0,res=0;
  for(I i=0;i<n;i++){
    Lf p1=i-1>=0?1-p_arr[i-1]:1,p2=p_arr[i],p3=i+1<n?1-p_arr[i+1]:1;
    Lf xf=(x0+v0+p1)*p2,vf=(v0+2*a0+3*p1)*p2,af=(a0+p1)*p2;
    tie(x0,v0,a0)=tie(xf,vf,af),res+=x0*p3;
  }
  printf("%.15Lf\n",res);
}