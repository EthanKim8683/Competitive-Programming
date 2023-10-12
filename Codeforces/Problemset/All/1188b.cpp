#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3e5;
I a_arr[N];
map<Lli,Lli>cnts;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli n,p,k;cin>>n>>p>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli res=0;
  for(I i=0;i<n;i++){
    Lli a=a_arr[i],cur=a;
    (cur*=cur)%=p;
    (cur*=cur)%=p;
    (cur-=k*a)%=p;
    (cur+=p)%=p;
    res+=cnts[cur];
    cnts[cur]++;
  }
  printf("%lli\n",res);
}
/*
(a[i] + a[j]) * (a[i] ** 2 + a[j] ** 2) = k mod p
(a[i] ** 2 - a[j] ** 2) * (a[i] ** 2 + a[j] ** 2) = k * (a[i] - a[j]) mod p
a[i] ** 4 - a[j] ** 4 = k * (a[i] - a[j]) mod p
a[i] ** 4 - a[j] ** 4 = k * a[i] - k * a[j] mod p
a[i] ** 4 - k * a[i] = a[j] ** 4 - k * a[j] mod p
*/