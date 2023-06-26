#include<bits/stdc++.h>
using namespace std;
using I=int;
const I M=2e5;
I a_arr[2][M];
I pats1[2*M],pats2[2][2*M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I m;cin>>m;
    for(I i=0;i<2;i++)for(I j=0;j<m;j++)cin>>a_arr[i][j];
    for(I i=0;i<2;i++)for(I j=0;j<m;j++)pats1[j*2+(j+i)%2]=a_arr[i][j];
    for(I i=0;i<m;i++)pats2[0][i]=a_arr[0][i],pats2[1][i]=a_arr[1][i];
    for(I i=0;i<m;i++)pats2[0][m+i]=a_arr[1][m-1-i],pats2[1][m+i]=a_arr[0][m-1-i];
    for(I i=0;i<2*m;i++)pats1[i]-=i,pats2[0][i]-=i,pats2[1][i]-=i;
    for(I i=0;i<m;i++){
      // upper_bound(pats2[i%2],pats2[i%2]+)
    }
  }
}