#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=150000;
const I A=150000;

I a_arr[N];
B viss[A+2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  I res=0;
  for(I i=n-1;i>=0;i--){
    I a=a_arr[i];
    if(!viss[a+1])viss[a+1]=1,res++;
    else if(!viss[a])viss[a]=1,res++;
    else if(a-1>0&&!viss[a-1])viss[a-1]=1,res++;
  }
  printf("%i\n",res);
}