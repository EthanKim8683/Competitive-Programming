#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,a,b;cin>>n>>a>>b;
    B res=0;
    if(a==n&&b==n)res=1;
    if(n-a-b>=2)res=1;
    printf("%s\n",res?"Yes":"No");
  }
}