#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  Lli res=0;
  for(I i=2;i+1<=n;i++)res+=i*(i+1);
  printf("%lli\n",res);
}