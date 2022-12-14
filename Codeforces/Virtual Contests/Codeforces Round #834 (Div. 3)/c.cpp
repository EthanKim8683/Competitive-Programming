#include<bits/stdc++.h>
using namespace std;
using I=int;
const I MAX=1e9;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I l,r,x;cin>>l>>r>>x;
    I a,b;cin>>a>>b;
    I lft=a==l?0:MAX;
    I rgt=a==r?0:MAX;
    I cen=a==b?0:MAX;
    lft=min(lft,abs(l-a)>=x?1:MAX);
    rgt=min(rgt,abs(r-a)>=x?1:MAX);
    cen=min(cen,abs(b-a)>=x?1:MAX);
    lft=min(lft,abs(l-r)>=x?rgt+1:MAX);
    rgt=min(rgt,abs(r-l)>=x?lft+1:MAX);
    cen=min(cen,abs(b-r)>=x?rgt+1:MAX);
    cen=min(cen,abs(b-l)>=x?lft+1:MAX);
    printf("%i\n",cen==MAX?-1:cen);
  }
}