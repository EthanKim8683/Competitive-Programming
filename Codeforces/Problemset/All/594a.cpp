#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=200000;
const I MAX=1e9;
I x_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  sort(x_arr,x_arr+n);
  I m=n-(n/2-1),res=MAX;
  for(I i=0;i+m-1<n;i++)res=min(res,x_arr[i+m-1]-x_arr[i]);
  printf("%i\n",res);
}
/*
Vova will always remove positions from either end since doing so eliminates
positions Lesha would never ban optimally

meanwhile, of the positions Vova should not ban, Lesha should ban all but the
farthest two, since banning a position Vova would ban would allow Vova to
choose an even narrower range

now the problem is simplified to finding the narrowest range possible after
banning n / 2 - 1 positions
*/