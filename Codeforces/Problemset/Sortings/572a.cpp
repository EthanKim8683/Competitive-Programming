#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N1=1e5;
const I N2=1e5;
I a_arr[N1];
I b_arr[N2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n1,n2;cin>>n1>>n2;
  I k,m;cin>>k>>m;
  for(I i=0;i<n1;i++)cin>>a_arr[i];
  for(I i=0;i<n2;i++)cin>>b_arr[i];
  printf("%s\n",a_arr[k-1]<b_arr[n2-m]?"YES":"NO");
}