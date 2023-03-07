#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=300000;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli tot1=0,tot2=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i],cur1=a/2,cur2=a-cur1;
    if(i%2)swap(cur1,cur2);
    tot1+=cur1,tot2+=cur2;
  }
  printf("%lli\n",min(tot1,tot2));
}