#include<bits/stdc++.h>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I r,g,b;cin>>r>>g>>b;
  r=r/2+r%2;
  g=g/2+g%2;
  b=b/2+b%2;
  r*=3;
  g*=3;
  b*=3;
  r-=3;
  g-=2;
  b-=1;
  printf("%i\n",max(r,max(g,b))+30);
}