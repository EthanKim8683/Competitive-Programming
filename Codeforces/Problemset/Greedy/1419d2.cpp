#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;

I a_arr[N];
I ress[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  I j=0;
  for(I i=1;i<n;i+=2)ress[i]=a_arr[j++];
  for(I i=0;i<n;i+=2)ress[i]=a_arr[j++];
  I res=0;
  for(I i=1;i+1<n;i++)res+=ress[i-1]>ress[i]&&ress[i+1]>ress[i];
  printf("%i\n",res);
  for(I i=0;i<n;i++)printf("%i ",ress[i]);
}