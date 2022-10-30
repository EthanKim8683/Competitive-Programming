#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=2000;

I a_arr[N];
I ps[26][N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<26;i++)for(I j=0;j<=n;j++)ps[i][j]=0;
    for(I i=0;i<n;i++){I a;cin>>a,a_arr[i]=a-1;}
    for(I i=0;i<n;i++)ps[a_arr[i]][i+1]++;
    for(I i=0;i<26;i++)for(I j=0;j<n;j++)ps[i][j+1]+=ps[i][j];
    I res=0;
    for(I i=0;i<26;i++){
      I r=n;
      for(I l=0;l<=n;l++){
        while(l<=r&&ps[i][l]-ps[i][0]>ps[i][n]-ps[i][r])r--;
        if(l>r)break;
        I cur=2*(ps[i][l]-ps[i][0]);
        for(I j=0;j<26;j++)res=max(res,cur+ps[j][r]-ps[j][l]);
      }
    }
    printf("%i\n",res);
  }
}