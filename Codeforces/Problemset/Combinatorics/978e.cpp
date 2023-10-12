#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1000;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,w;cin>>n>>w;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I low=0,upp=w;
  for(I i=n-1;i>=0;i--){
    I a=a_arr[i];
    low=max(low-a,0);
    upp=min(upp-a,w);
  }
  printf("%i\n",max(upp-low+1,0));
}
/*
we can maintain the range of passenger counts before each stop from the final
stop to the first stop, shrinking the range if according to the set of
passenger counts allowed on the bus ([0, w])
*/