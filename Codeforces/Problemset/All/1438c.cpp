#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
const I M=100;
I a_arr[N][M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>a_arr[i][j];
    for(I i=0;i<n;i++){
      for(I j=0;j<m;j++){
        I a=a_arr[i][j];
        printf("%i ",a+(a+i+j)%2);
      }
      printf("\n");
    }
  }
}