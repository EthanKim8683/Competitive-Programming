#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
map<I,I>cnts1,cnts2;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    cnts1[x-y]++;
    cnts2[x+y]++;
  }
  Lli res=0;
  for(auto[z,cnt]:cnts1)res+=(Lli)cnt*(cnt-1)/2;
  for(auto[z,cnt]:cnts2)res+=(Lli)cnt*(cnt-1)/2;
  printf("%lli\n",res);
}