#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;
const I C=5000;
const I MAX=1e9;

I c_arr[N];
I ps[2*C+1];

I main(){
#ifndef ETHANKIM8683
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>c_arr[i];
  sort(c_arr,c_arr+n);
  for(I i=0;i<n;i++)ps[c_arr[i]-1]++;
  for(I i=C-1;i-1>=0;i--)ps[i-1]+=ps[i];
  I res=MAX;
  for(I i=0;i<n;i++){
    I c=c_arr[i];
    res=min(res,ps[2*c]+i);
  }
  printf("%i\n",res);
}