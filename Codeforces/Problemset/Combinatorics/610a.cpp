#include<bits/stdc++.h>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  if(n%2)printf("0\n"),exit(0);
  n/=2;
  printf("%i\n",(n-1)/2);
}