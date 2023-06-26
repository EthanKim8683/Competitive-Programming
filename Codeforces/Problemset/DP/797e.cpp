#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100000;
const I SQTN=317;
I a_arr[N];
I ress[SQTN+1][N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I siz=sqrt(n);
  for(I i=siz;i>=1;i--)for(I j=n-1;j>=0;j--)ress[i][j]=j+a_arr[j]+i>=n?1:ress[i][j+a_arr[j]+i]+1;
  I q;cin>>q;
  while(q--){
    I p,k;cin>>p>>k,p--;
    if(k<=siz){printf("%i\n",ress[k][p]);continue;}
    I res=0;
    while(p<n)res++,p+=a_arr[p]+k;
    printf("%i\n",res);
  }
}