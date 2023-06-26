#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100000;
I h_arr[N];
I stds[N];
I lows[N],upps[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>h_arr[i];
  copy_n(h_arr,n,stds);
  sort(stds,stds+n);
  for(I i=0;i<n;i++){
    I h=h_arr[i];
    I low=lower_bound(stds,stds+n,h)-stds;
    I upp=upper_bound(stds,stds+n,h)-stds-1;
    if(low<=i&&i<=upp)lows[i]++,upps[i]++;
    else if(i>upp)lows[upp]++,upps[i]++;
    else if(i<low)lows[i]++,upps[low]++;
  }
  I res=0,cur=0;
  for(I i=0;i<n;i++)cur+=lows[i]-upps[i],res+=cur==0;
  printf("%i\n",res);
}