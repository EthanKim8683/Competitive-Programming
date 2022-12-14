#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli cur=1,res=1;
  for(I i=1;i<n;i++){
    I a=a_arr[i],b=a_arr[i-1];
    cur+=1;
    cur+=(a!=b)*i;
    res+=cur;
  }
  while(m--){
    I i,x;cin>>i>>x,i--;
    I a=a_arr[i];
    if(i>0){
      I b=a_arr[i-1];
      res+=(Lli)((x!=b)-(a!=b))*(n-i)*i;
    }
    if(i<n-1){
      I b=a_arr[i+1];
      res+=(Lli)((x!=b)-(a!=b))*(i+1)*(n-i-1);
    }
    a_arr[i]=x;
    printf("%lli\n",res);
  }
}