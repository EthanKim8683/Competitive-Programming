#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2000;
I a_arr[N];
I gcd(I a,I b){
  return b?gcd(b,a%b):a;
}
B cmp(I a,I b){
  return a%2<b%2;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n,cmp);
    I res=0;
    for(I i=0;i<n;i++)for(I j=i+1;j<n;j++)res+=gcd(a_arr[i],2*a_arr[j])>1;
    printf("%i\n",res);
  }
}