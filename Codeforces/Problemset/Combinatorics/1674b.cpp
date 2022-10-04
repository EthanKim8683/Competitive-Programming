#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I a=s[0]-'a',b=s[1]-'a';
    printf("%i\n",a*26+b-a-(b>a)+1);
  }
}