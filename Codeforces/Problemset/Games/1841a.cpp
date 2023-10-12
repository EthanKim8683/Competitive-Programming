#include<bits/stdc++.h>
using namespace std;
using I=int;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    printf("%s\n",n>4?"Alice":"Bob");
  }
}