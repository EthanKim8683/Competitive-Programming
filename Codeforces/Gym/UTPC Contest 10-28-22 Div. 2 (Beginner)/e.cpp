#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
Lli a_arr[N];
priority_queue<Lli>hols;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli res=0;
  for(I i=n-1;i>=0;i--){
    I a=a_arr[i];
    if(i%2){
      hols.push(a);
      continue;
    }
    if(!hols.size()){
      res+=a;
      continue;
    }
    I b=hols.top();
    if(b>a){
      res+=b;
      hols.pop();
      hols.push(a);
      continue;
    }
    res+=a;
  }
  printf("%lli\n",res);
}