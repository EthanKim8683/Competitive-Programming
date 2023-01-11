#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100000;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    B res1=0,res2=0;
    if(n==1)res1=res2=a_arr[0]==k;
    for(I i=0;i<n;i++)res1|=a_arr[i]==k;
    for(I i=0;i<n;i++)for(I j=1;j<3&&i+j<n;j++)res2|=a_arr[i]>=k&&a_arr[i+j]>=k;
    printf("%s\n",res1&&res2?"yes":"no");
  }
}