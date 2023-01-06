#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e6;
const I M=1e6;
I a_arr[N];
I b_arr[M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,p;cin>>n>>m>>p;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<m;i++)cin>>b_arr[i];
  I res=0;
  for(I i=0;i<n;i++)if(a_arr[i]%p){res+=i;break;}
  for(I i=0;i<m;i++)if(b_arr[i]%p){res+=i;break;}
  printf("%i\n",res);
}