#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I M=262144;

I p_arr[M];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I m;cin>>m;
    for(I i=0;i<m;i++)cin>>p_arr[i];
    I n=31-__builtin_clz(m);
    B vld=1;
    I res=0;
    for(I i=m;i/2;i/=2){
      for(I j=0;j<m;j+=i){
        I a=*min_element(p_arr+j+0,p_arr+j+i/2);
        I b=*max_element(p_arr+j+0,p_arr+j+i/2);
        I c=*min_element(p_arr+j+i/2,p_arr+j+i);
        I d=*max_element(p_arr+j+i/2,p_arr+j+i);
        vld&=b-a+1==i/2;
        vld&=d-c+1==i/2;
        vld&=abs(d-b)==i/2;
        vld&=abs(c-a)==i/2;
        res+=b>d;
      }
    }
    printf("%i\n",vld?res:-1);
  }
}