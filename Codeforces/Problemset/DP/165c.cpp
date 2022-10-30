#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const I N=1e6;

I ps[N+1];
map<I,I>cnts;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>k;
  S s;cin>>s;
  I n=s.size();
  for(I i=0;i<n;i++)ps[i+1]=s[i]=='1';
  for(I i=0;i<n;i++)ps[i+1]+=ps[i];
  Lli res=0;
  for(I i=0;i<n;i++){
    cnts[ps[i]]++;
    res+=cnts[ps[i+1]-k];
  }
  printf("%lli\n",res);
}