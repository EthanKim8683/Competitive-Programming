#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using Lli=long long int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli n;cin>>n,n--;
  Lli res=0;
  for(Lli i=1;i<=n;i*=2)res+=(n+i)/(i*2)*i;
  printf("%lli\n",res);
  return 0;
}