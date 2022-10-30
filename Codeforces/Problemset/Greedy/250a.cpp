#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100;

I a_arr[N];
vector<I>ress;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I cnt=0;
  ress.push_back(0);
  for(I i=0;i<n;i++){
    cnt+=a_arr[i]<0;
    if(cnt==3)ress.push_back(0),cnt=1;
    ress.back()++;
  }
  printf("%i\n",ress.size());
  for(auto i:ress)printf("%i ",i);
}