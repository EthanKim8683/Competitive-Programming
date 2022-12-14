#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I dif=0;
    for(I i=0;i<n;i++)dif^=a_arr[i];
    if(dif==0){printf("DRAW\n");continue;}
    I log=31-__builtin_clz(dif),cnt=0;
    for(I i=0;i<n;i++)cnt+=a_arr[i]>>log&1;
    printf("%s\n",cnt%4==1||(n-cnt)%2?"WIN":"LOSE");
  }
}