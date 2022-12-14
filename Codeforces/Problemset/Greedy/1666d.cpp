#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
I cnts1[26];
I cnts2[26];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s,t;cin>>s>>t;
    fill_n(cnts1,26,0);
    fill_n(cnts2,26,0);
    for(auto c:s)cnts1[c-'A']++;
    for(auto c:t)cnts2[c-'A']++;
    S res="";
    for(auto c:s)if(--cnts1[c-'A']<cnts2[c-'A'])res+=c;
    printf("%s\n",res==t?"YES":"NO");
  }
}