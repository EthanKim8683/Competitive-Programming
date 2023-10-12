#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S n;cin>>n;
    printf("%c\n",n.size()>2?*min_element(n.begin(),n.end()):n[1]);
  }
}