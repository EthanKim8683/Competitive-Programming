#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using S=string;
const Lli MOD=998244353;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  Lli len1=0;
  for(;len1<n;len1++)if(s[0]!=s[len1])break;
  Lli len2=0;
  for(;len2<n;len2++)if(s[n-1]!=s[n-1-len2])break;
  printf("%lli\n",s[0]==s[n-1]?(Lli)(len1+1)*(len2+1)%MOD:len1+len2+1);
}
/*
after removing the substring, the remaining prefix and suffix must both
consist of only the same character

therefore, we can find the lengths of the maximal same-character prefix and
suffix

if they are of the same character, any prefix of the prefix and any suffix of
the suffix may be used

if they are different characters, only either a prefix of the prefix or a
suffix or a suffix may be used
*/