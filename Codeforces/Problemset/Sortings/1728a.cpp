#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=20;
I cnts[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>cnts[i];
    printf("%i\n",max_element(cnts,cnts+n)-cnts+1);
  }
}