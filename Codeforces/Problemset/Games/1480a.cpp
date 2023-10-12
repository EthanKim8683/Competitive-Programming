#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    for(I i=0;i<s.size();i++){
      if(i%2==0)s[i]=s[i]=='a'?'b':'a';
      if(i%2==1)s[i]=s[i]=='z'?'y':'z';
    }
    printf("%s\n",s.c_str());
  }
}