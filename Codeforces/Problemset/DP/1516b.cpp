#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=2000;

I a_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    B res=0;
    I tar=0;
    for(I i=0;i<n;i++){
      tar^=a_arr[i];
      I cur=0,cnt=0;
      for(I j=i+1;j<n;j++){
        cur^=a_arr[j];
        if(cur==tar)cur=0,cnt++;
      }
      res|=cur==0&&cnt;
    }
    printf("%s\n",res?"YES":"NO");
  }
}