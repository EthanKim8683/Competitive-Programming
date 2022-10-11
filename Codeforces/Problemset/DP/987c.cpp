#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=3000;
const I MAX=1e9;

I s_arr[N];
I c_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>s_arr[i];
  for(I i=0;i<n;i++)cin>>c_arr[i];
  I res=MAX;
  for(I i=0;i<n;i++){
    I cur1=MAX,cur2=MAX;
    for(I j=0;j<i;j++)if(s_arr[j]<s_arr[i])cur1=min(cur1,c_arr[j]);
    for(I j=i+1;j<n;j++)if(s_arr[j]>s_arr[i])cur2=min(cur2,c_arr[j]);
    res=min(res,cur1+cur2+c_arr[i]);
  }
  printf("%i\n",res==MAX?-1:res);
}