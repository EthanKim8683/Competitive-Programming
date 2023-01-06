#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    if(n==1){printf("a\n");continue;}
    S res="";
    if(n%2){
      n-=2;
      I low=n/2,upp=n-low;
      res+=S(low,'a');
      res+="b";
      res+="c";
      res+=S(upp,'a');
    }else{
      n-=1;
      I low=n/2,upp=n-low;
      res+=S(low,'a');
      res+="b";
      res+=S(upp,'a');
    }
    printf("%s\n",res.c_str());
  }
}