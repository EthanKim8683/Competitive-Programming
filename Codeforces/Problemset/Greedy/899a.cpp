#include<bits/stdc++.h>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  I cnt1=0,cnt2=0;
  for(I i=0;i<n;i++){
    I a;cin>>a;
    cnt1+=a==1;
    cnt2+=a==2;
  }
  I res=min(cnt1,cnt2);
  cnt1-=res;
  cnt2-=res;
  res+=cnt1/3;
  printf("%i\n",res);
}