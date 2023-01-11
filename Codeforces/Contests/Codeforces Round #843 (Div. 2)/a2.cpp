#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    S a=s.substr(0,1),b=s.substr(1,n-2),c=s.substr(n-1,1);
    if(((b<=a&&b<=c)||(b>=a&&b>=c))){printf("%s %s %s\n",a.c_str(),b.c_str(),c.c_str());continue;}
    a=s.substr(0,1),b=s.substr(1,1),c=s.substr(2,n-2);
    if(((b<=a&&b<=c)||(b>=a&&b>=c))){printf("%s %s %s\n",a.c_str(),b.c_str(),c.c_str());continue;}
    a=s.substr(0,n-2),b=s.substr(n-2,1),c=s.substr(n-1,1);
    if(((b<=a&&b<=c)||(b>=a&&b>=c))){printf("%s %s %s\n",a.c_str(),b.c_str(),c.c_str());continue;}
    printf(":(\n");
  }
}