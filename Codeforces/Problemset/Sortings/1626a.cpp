#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
I cnts[26];
vector<I>twos;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    fill_n(cnts,26,0);
    for(auto c:s)cnts[c-'a']++;
    twos.clear();
    for(I i=0;i<26;i++)if(cnts[i]==2)twos.push_back(i);
    for(auto i:twos)printf("%c",i+'a');
    for(auto i:twos)printf("%c",i+'a');
    for(I i=0;i<26;i++)if(cnts[i]==1)printf("%c",i+'a');
    printf("\n");
  }
}