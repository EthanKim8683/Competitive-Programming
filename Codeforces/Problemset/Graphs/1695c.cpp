#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1000;
const I M=1000;
const I MIN=-1e9;
const I MAX=1e9;

I cels[N][M];
I mins[N][M],maxs[N][M];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)for(I j=0;j<m;j++)
      cin>>cels[i][j],mins[i][j]=MAX,maxs[i][j]=MIN;
    if((n+m)%2==0){printf("NO\n");continue;}
    mins[0][0]=maxs[0][0]=cels[0][0];
    for(I i=0;i<n;i++)for(I j=0;j<m;j++){
      if(i+1<n){
        mins[i+1][j]=min(mins[i+1][j],mins[i][j]+cels[i+1][j]);
        maxs[i+1][j]=max(maxs[i+1][j],maxs[i][j]+cels[i+1][j]);
      }
      if(j+1<m){
        mins[i][j+1]=min(mins[i][j+1],mins[i][j]+cels[i][j+1]);
        maxs[i][j+1]=max(maxs[i][j+1],maxs[i][j]+cels[i][j+1]);
      }
    }
    if(mins[n-1][m-1]<=0&&0<=maxs[n-1][m-1])printf("YES\n");
    else printf("NO\n");
  }
  return 0;
}