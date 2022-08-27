#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using Lli=long long int;

vector<I>ress;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n/4;i++){
    ress.push_back(1+i*2);
    ress.push_back((n&~1)-i*2);
  }
  if(n%4==1)ress.push_back(n/2);
  else if(n%4==2)ress.push_back(n/2);
  else if(n%4==3)ress.push_back(n);
  printf("%i\n",(n/2%2)^(n%2));
  printf("%i ",ress.size());
  for(auto res:ress)printf("%i ",res);
  return 0;
}