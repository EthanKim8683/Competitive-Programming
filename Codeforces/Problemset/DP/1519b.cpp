#include<bits/stdc++.h>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m,k;cin>>n>>m>>k;
    printf("%s\n",n*m-1==k?"YES":"NO");
  }
}