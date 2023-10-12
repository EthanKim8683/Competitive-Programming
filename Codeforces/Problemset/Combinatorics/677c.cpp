#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using S=string;
const Lli MOD=1e9+7;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  Lli res=1;
  auto con=[&](I x){
    for(I i=0;i<6;i++)if(~x>>i&1)(res*=3)%=MOD;
  };
  for(auto c:s){
    if(c>='0'&&c<='9')con(c-'0');
    if(c>='A'&&c<='Z')con(c-'A'+10);
    if(c>='a'&&c<='z')con(c-'a'+36);
    if(c=='-')con(62);
    if(c=='_')con(63);
  }
  printf("%lli\n",res);
}
/*
if the ith bit is positive, both words must be positive at the ith bit

if the ith bit is negative, at least one word must be negative at the ith bit
*/