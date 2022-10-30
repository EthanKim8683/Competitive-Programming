#include<bits/stdc++.h>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m,n;cin>>n>>m;
  printf("%i\n",m/2*n+m%2*n/2);
}