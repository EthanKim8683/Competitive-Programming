#include<bits/stdc++.h>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I a,b;cin>>a>>b;
    I res=b-a;
    for(I i=0;i<b-a;i++)res=min(res,i+((a+i|b+0)-(b+0))+1);
    for(I i=0;i<b-a;i++)res=min(res,i+((a+0|b+i)-(b+i))+1);
    printf("%i\n",res);
  }
}