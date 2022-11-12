#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const I A=26;

I x_arr[A];
map<Lli,I>cnts[A];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  for(I i=0;i<A;i++)cin>>x_arr[i];
  S s;cin>>s;
  I n=s.size();
  Lli res=0,sum=0;
  for(I i=0;i<n;i++){
    I c=s[i]-'a';
    res+=cnts[c][sum];
    sum+=x_arr[c];
    cnts[c][sum]++;
  }
  printf("%lli\n",res);
}