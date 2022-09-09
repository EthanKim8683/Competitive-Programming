#include<iostream>
#include<cstdio>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    printf("%i\n",max(n-2,0));
  }
  return 0;
}