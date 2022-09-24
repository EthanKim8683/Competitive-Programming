#include<bits/stdc++.h>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  printf("%i\n",n%2?0:1<<(n/2));
}