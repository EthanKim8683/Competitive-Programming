#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const I N=100;

I cnts[26];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    S s;cin>>s;
    cnts[s[0]-'a']++;
  }
  Lli res=0;
  for(I i=0;i<26;i++){
    I cnt=cnts[i];
    Lli a=cnt/2,b=cnt/2+cnt%2;
    res+=a*(a-1)/2;
    res+=b*(b-1)/2;
  }
  printf("%lli\n",res);
}