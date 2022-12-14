#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
Lli a_arr[N];
Lli gcd(Lli a,Lli b){
  return b?gcd(b,a%b):a;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  Lli num=0,cur=0;
  for(I i=1;i<n;i++){
    cur+=(a_arr[i]-a_arr[i-1])*i;
    num+=2*cur;
  }
  num+=accumulate(a_arr,a_arr+n,0ll);
  Lli den=n,fac=gcd(num,den);
  num/=fac,den/=fac;
  printf("%lli %lli\n",num,den);
}