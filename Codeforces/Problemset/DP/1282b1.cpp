#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=2e5;

I a_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,p,k;cin>>n>>p>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    I rem1=p,tot1=0;
    for(I i=1;i<n;i+=2)if((rem1-=a_arr[i])>=0)tot1+=2;
    I rem2=p-a_arr[0],tot2=rem2>=0;
    for(I i=2;i<n;i+=2)if((rem2-=a_arr[i])>=0)tot2+=2;
    printf("%i\n",max(tot1,tot2));
  }
}