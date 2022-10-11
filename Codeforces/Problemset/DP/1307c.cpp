#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const I N=1e5;

Lli cnts[26];
Lli tots[26][26];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  for(auto c:s){
    c-='a';
    for(I i=0;i<26;i++)tots[i][c]+=cnts[i];
    cnts[c]++;
  }
  Lli res=*max_element(cnts,cnts+26);
  for(I i=0;i<26;i++)for(I j=0;j<26;j++)res=max(res,tots[i][j]);
  printf("%lli\n",res);
}