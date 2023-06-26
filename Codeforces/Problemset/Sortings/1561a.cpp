#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=999;
I a_arr[N];
I stds[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    copy_n(a_arr,n,stds);
    sort(stds,stds+n);
    I res=0;
    for(I i=0;i<2*n;i++){
      B std=1;
      for(I j=0;j<n;j++)std&=a_arr[j]==stds[j];
      if(std)break;
      for(I j=i%2;j+1<n;j+=2)if(a_arr[j]>a_arr[j+1])swap(a_arr[j],a_arr[j+1]);
      res++;
    }
    printf("%i\n",res);
  }
}