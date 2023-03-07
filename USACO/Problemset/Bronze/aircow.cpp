#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100000;
I p_arr[N];
I t_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>p_arr[i];
  for(I i=0;i<n;i++)cin>>t_arr[i];
  Lli cur=0,res=0;
  for(I i=0;i<n;i++){
    Lli dif=p_arr[i]-t_arr[i];
    if(cur*dif<=0)cur=0;
    res+=max(abs(dif)-abs(cur),0ll);
    cur=dif;
  }
  printf("%lli\n",res);
}