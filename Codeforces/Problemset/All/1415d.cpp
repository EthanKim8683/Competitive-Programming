#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
const I MAX=1e9;
I a_arr[N];
map<I,I>cnts;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cnts[__builtin_clz(a_arr[i])]++;
  for(auto[nlz,cnt]:cnts)if(cnt>2)printf("1"),exit(0);
  I res=MAX;
  for(I i=0;i+1<n;i++){
    I low=0;
    for(I j=i;j>=0;j--){
      low^=a_arr[j];
      I upp=0;
      for(I k=i+1;k<n;k++){
        upp^=a_arr[k];
        if(low<=upp)continue;
        res=min(res,k-j-1);
      }
    }
  }
  printf("%i\n",res==MAX?-1:res);
}