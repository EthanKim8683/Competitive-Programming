#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
map<C,I>cnts;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  for(auto c:s)cnts[c]++;
  while(cnts['o']&&cnts['n']&&cnts['e']){
    printf("1 ");
    cnts['o']--,cnts['n']--,cnts['e']--;
  }
  while(cnts['z']&&cnts['e']&&cnts['r']&&cnts['o']){
    printf("0 ");
    cnts['z']--,cnts['e']--,cnts['r']--,cnts['o']--;
  }
}