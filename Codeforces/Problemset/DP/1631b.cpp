#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=2e5;

I a_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I val=a_arr[n-1],upp=n,res=0;
    for(I i=n-2;i>=0;i--)
      if(i<upp&&a_arr[i]!=val)
        upp=i+1-(n-(i+1)),res++;
    printf("%i\n",res);
  }
}