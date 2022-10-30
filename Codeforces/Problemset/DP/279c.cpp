#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;

I a_arr[N];
I lows[N],upps[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I low=0,upp=0;
  for(I i=1;i<n;i++){
    if(a_arr[i-1]<a_arr[i])upp=i;
    if(a_arr[i-1]>a_arr[i])low=i;
    lows[i]=low,upps[i]=upp;
  }
  while(m--){
    I l,r;cin>>l>>r,l--,r--;
    I upp=upps[r],low=lows[upp];
    printf("%s\n",low<=l?"Yes":"No");
  }
}