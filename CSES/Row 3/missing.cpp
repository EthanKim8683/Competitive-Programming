#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
I x_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  sort(x_arr,x_arr+n);
  Lli pre=0;
  for(I i=0;i<n;i++){
    I x=x_arr[i];
    if(x>pre+1)printf("%lli\n",pre+1),exit(0);
    pre+=x;
  }
  printf("%lli\n",pre+1);
}