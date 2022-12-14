#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
using B=bool;
C chrs[]="Yes";
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    B res=0;
    for(I i=0;i<3;i++){
      B cur=1;
      for(I j=0;j<n;j++)cur&=s[j]==chrs[(i+j)%3];
      res|=cur;
    }
    printf("%s\n",res?"YES":"NO");
  }
}