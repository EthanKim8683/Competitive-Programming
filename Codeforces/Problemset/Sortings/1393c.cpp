#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
I a_arr[N];
I cnts[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    fill_n(cnts,n+1,0);
    for(I i=0;i<n;i++)cnts[a_arr[i]]++;
    I j=max_element(cnts,cnts+n+1)-cnts,res=0;
    for(I i=0;i<n+1;i++)if(i!=j)res+=cnts[i]-(cnts[i]==cnts[j]);
    printf("%i\n",res/(cnts[j]-1));
  }
}