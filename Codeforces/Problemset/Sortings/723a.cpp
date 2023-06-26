#include<bits/stdc++.h>
using namespace std;
using I=int;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I x1,x2,x3;cin>>x1>>x2>>x3;
  printf("%i\n",max(max(x1,x2),x3)-min(min(x1,x2),x3));
}