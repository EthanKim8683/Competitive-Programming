#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I M=N;
I x_arr[M];
set<I>bnds;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k,a;cin>>n>>k>>a;
  I m;cin>>m;
  for(I i=0;i<m;i++)cin>>x_arr[i];
  bnds.insert(0),bnds.insert(n+1);
  I res=(n+1)/(a+1);
  for(I i=0;i<m;i++){
    if(res<k)printf("%i",i),exit(0);
    I x=x_arr[i];
    if(bnds.find(x)!=bnds.end())printf("%i",i+1),exit(0);
    I y=*prev(bnds.lower_bound(x));
    I z=*bnds.upper_bound(x);
    res-=(z-y)/(a+1);
    res+=(x-y)/(a+1)+(z-x)/(a+1);
    bnds.insert(x);
  }
  printf("%i",res<k?m:-1);
}