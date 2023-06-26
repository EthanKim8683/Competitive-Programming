#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2000;
I y_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>y_arr[i];
  sort(y_arr,y_arr+n);
  I res=0;
  for(I i=0;i+3<=n;i+=3){
    I cur=0;
    for(I j=0;j<3;j++)cur=max(cur,y_arr[i+j]);
    res+=5-cur>=k;
  }
  printf("%i\n",res);
}