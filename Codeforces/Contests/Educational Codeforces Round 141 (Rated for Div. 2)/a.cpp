#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=50;
I a_arr[N];
vector<I>rems;
vector<I>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n,greater<I>());
    ress.clear(),rems.clear();
    I sum=0;
    for(I i=0;i<n;i++){
      I a=a_arr[i];
      if(a==sum){rems.push_back(a);continue;}
      sum+=a;
      ress.push_back(a);
    }
    B vld=1;
    for(auto rem:rems){
      vld&=rem!=sum;
      sum+=rem;
      ress.push_back(rem);
    }
    if(!vld){printf("NO\n");continue;}
    printf("YES\n");
    for(auto res:ress)printf("%i ",res);
    printf("\n");
  }
}
