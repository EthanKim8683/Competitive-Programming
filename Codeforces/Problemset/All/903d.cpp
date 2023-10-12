#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200000;
I a_arr[N];
map<I,I>cnts;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli res=0,pre=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    res+=(Lli)a*i-pre+cnts[a+1]-cnts[a-1];
    pre+=a,cnts[a]++;
  }
  printf("%lli\n",res);
}