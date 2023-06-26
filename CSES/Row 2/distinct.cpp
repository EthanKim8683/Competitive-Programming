#include<bits/stdc++.h>
using namespace std;
using I=int;
set<I>vals;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x;cin>>x;
    vals.insert(x);
  }
  printf("%i\n",vals.size());
}