#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lf=long double;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  Lf res=0;
  for(I i=1;i<=n;i++)res+=1.0/i;
  printf("%Lf\n",res);
}