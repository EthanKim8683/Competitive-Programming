#include<bits/stdc++.h>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k1,k2;cin>>n>>k1>>k2;
    I w,b;cin>>w>>b;
    I l1=n-k1,l2=n-k2;
    I m1=min(k1,k2),m2=min(l1,l2);
    I n1=max(k1,k2),n2=max(l1,l2);
    w-=min(m1,w);
    b-=min(m2,b);
    w-=min((n1-m1)/2,w);
    b-=min((n2-m2)/2,b);
    printf("%s\n",w||b?"NO":"YES");
  }
}