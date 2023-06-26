#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  I cnt=0,cst=0,tot=10;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(tot+a>720)break;
    cnt++,tot+=a,cst+=max(tot-360,0);
  }
  printf("%i %i\n",cnt,cst);
}