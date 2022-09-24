#include<iostream>
#include<cstdio>
#include<set>
#include<vector>

using namespace std;

using I=int;
using S=string;

const I N=1000;

set<S>viss1,viss2;
vector<S>ress;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    S a,b;cin>>a>>b;
    S c=a.substr(0,3);
    S d=a.substr(0,2)+b.substr(0,1);
    if(viss1.find(d)==viss1.end()){
      ress.push_back(d);
      viss1.insert(d);
      viss2.insert(c);
    }else{
      if(viss1.find(c)!=viss1.end()||viss2.find(c)!=viss2.end()){printf("NO\n");exit(0);}
      ress.push_back(c);
      viss1.insert(c);
    }
  }
  printf("YES\n");
  for(auto s:ress)printf("%s\n",s.c_str());
}