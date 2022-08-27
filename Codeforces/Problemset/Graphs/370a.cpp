#include<iostream>
#include<cstdio>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I r1,c1,r2,c2;cin>>r1>>c1>>r2>>c2,r1--,c1--,r2--,c2--;
  printf("%i ",2-(r1==r2)-(c1==c2));
  if((r1+c1)%2!=(r2+c2)%2)printf("0 ");
  else printf("%i ",2-(r1+c1==r2+c2)-(r1-c1==r2-c2));
  printf("%i\n",max(abs(r1-r2),abs(c1-c2)));
  return 0;
}