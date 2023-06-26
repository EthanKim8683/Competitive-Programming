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
  I rem=accumulate(a_arr,a_arr+n,0),cur=0;
  for(I i=n-1;i>=0;i--){
    cur+=a_arr[i],rem-=a_arr[i];
    if(cur>rem)printf("%i\n",n-i),exit(0);
  }
}