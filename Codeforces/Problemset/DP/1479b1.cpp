#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
I a_arr[N];
I curs[2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I res=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(curs[0]!=a){curs[0]=a,res++;continue;}
    if(curs[1]!=a){curs[1]=a,res++;continue;}
  }
  printf("%i\n",res);
}