#include<bits/stdc++.h>
using namespace std;
using I=int;
const I M=2e5;
I s_arr[M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m,a,b;cin>>n>>m>>a>>b;
    for(I i=0;i<m;i++)cin>>s_arr[i];
    sort(s_arr,s_arr+m);
    I t1=a>b?n-a:a<b?a-1:0,t2=abs(a-b)-1,res=0;
    for(I i=0,j=m-1;i<t2&&j>=0;j--)if(i+s_arr[j]<=t1+t2)res++,i++;
    printf("%i\n",res);
  }
}