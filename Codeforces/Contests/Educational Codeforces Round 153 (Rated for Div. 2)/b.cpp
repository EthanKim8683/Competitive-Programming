#include<bits/stdc++.h>
using namespace std;
using I=int;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I m,k,a1,ak;cin>>m>>k>>a1>>ak;
    I dif1=min(m/k,ak);
    m-=dif1*k,ak-=dif1;
    I dif2=m/k;
    m-=dif2*k;
    I dif3=min(m,a1);
    m-=dif3,a1-=dif3;
    I dif4=m;
    m-=dif4;
    I dif5=min(a1/k,dif2);
    a1-=dif5*k,dif2-=dif5;
    printf("%i\n",dif2+dif4);
  }
}