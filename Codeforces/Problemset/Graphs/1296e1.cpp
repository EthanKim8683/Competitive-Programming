#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using S=string;
using C=char;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  C a='a',b='a';
  S res="";
  for(auto c:s){
    if(c>=a)res+='0',a=c;
    else if(c>=b)res+='1',b=c;
    else{printf("NO\n");return 0;}
  }
  printf("YES\n");
  printf("%s\n",res.c_str());
  return 0;
}