#include<bits/stdc++.h>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    I n;cin>>n;
    I res=0;
    if(n%4==0)n-=4,res+=1;
    if(n%4==1)n-=9,res+=1;
    if(n%4==2)n-=6,res+=1;
    if(n%4==3)n-=14,res+=2;
    printf("%i\n",n<0?-1:res+n/4);
  }
}