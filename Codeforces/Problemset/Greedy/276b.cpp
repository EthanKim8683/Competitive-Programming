#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

I cnts[26];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  for(auto c:s)cnts[c-'a']++;
  I cnt=0;
  for(I i=0;i<26;i++)cnt+=cnts[i]%2;
  if(cnt<=1)printf("First\n");
  else printf("%s\n",(cnt-1)%2?"Second":"First");
}