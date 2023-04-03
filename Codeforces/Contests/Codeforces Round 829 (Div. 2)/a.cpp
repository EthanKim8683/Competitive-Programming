#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;

const I N=100;

C msgs[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    cin>>msgs;
    I rem=0;
    for(I i=0;i<n;i++){
      rem+=msgs[i]=='Q';
      rem-=msgs[i]=='A';
      rem=max(rem,0);
    }
    printf("%s\n",rem>0?"No":"Yes");
  }
}