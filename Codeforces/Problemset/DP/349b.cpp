#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e6;

I a_arr[9];
I ress[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I v;cin>>v;
  for(I i=0;i<9;i++)cin>>a_arr[i];
  I low=*min_element(a_arr,a_arr+9);
  I len=v/low;
  if(len<=0)printf("-1\n"),exit(0);
  I cur=8;
  for(I i=0;i<len;i++){
    while(a_arr[cur]+(len-1-i)*low>v)cur--;
    v-=a_arr[cur],ress[i]=cur+1;
  }
  for(I i=0;i<len;i++)printf("%i",ress[i]);
}