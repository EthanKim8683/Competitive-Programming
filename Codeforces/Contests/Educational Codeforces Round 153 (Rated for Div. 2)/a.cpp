#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    S a="",b="";
    for(I i=0;i<s.size();i++)a+="()";
    for(I i=0;i<s.size();i++)b+="(";
    for(I i=0;i<s.size();i++)b+=")";
    if(a.find(s)==string::npos)printf("YES\n%s\n",a.c_str());
    else if(b.find(s)==string::npos)printf("YES\n%s\n",b.c_str());
    else printf("NO\n");
  }
}