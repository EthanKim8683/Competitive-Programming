#include<bits/stdc++.h>
using namespace std;
using I=int;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  I res=0,pow=1;
  for(;n;n/=10,pow*=2){
    I d=n%10;
    if(d==4)res+=1*pow;
    if(d==7)res+=2*pow;
  }
  printf("%i\n",res);
}