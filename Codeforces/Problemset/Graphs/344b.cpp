#include<iostream>
#include<cstdio>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I a,b,c;cin>>a>>b>>c;
  I x=a-b+c;
  if(x<0||x%2==1){printf("Impossible\n");return 0;}
  x/=2;
  I y=a-x,z=c-x;
  if(y<0||z<0){printf("Impossible\n");return 0;}
  printf("%i %i %i\n",y,z,x);
  return 0;
}