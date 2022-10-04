#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=100;

I a_arr[N];
I n;
I m;
I k;

B chk(I x){
  I sum=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(a>x)return 0;
    sum+=x-a;
  }
  return sum>=m;
}

I fnd(){
  I l=0,r=k;
  while(l<r){
    I x=l+(r-l)/2;
    if(chk(x))r=x;
    else l=x+1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  cin>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  k=*max_element(a_arr,a_arr+n)+m;
  printf("%i %i\n",fnd(),k);
}