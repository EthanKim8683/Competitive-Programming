#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=1000;

C cels[N][N+1];
I cons[N][4];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>cels[i];
    if(m%2){
      printf("YES\n");
      for(I i=0;i<=m;i++)printf("%i ",i%2+1);
      printf("\n");
      continue;
    }
    fill(&cons[0][0],&cons[0][0]+sizeof(cons)/sizeof(I),-1);
    for(I i=0;i<n;i++)for(I j=0;j<n;j++)if(i!=j)
      cons[i][(cels[i][j]-'a')<<1|(cels[j][i]-'a')]=j;
    I a=-1,b=-1,c=-1;
    for(I i=0;i<n;i++){
      I aa=cons[i][0b00],ab=cons[i][0b01],ba=cons[i][0b10],bb=cons[i][0b11];
      if(aa!=-1){a=i,b=aa,c=aa;break;}
      if(bb!=-1){a=i,b=bb,c=bb;break;}
      if(ab!=-1&&ba!=-1){a=i,b=ab,c=ba;break;}
    }
    if(a==-1&&b==-1&&c==-1){printf("NO\n");continue;}
    printf("YES\n");
    for(I i=0;i<m/2;i++)printf("%i ",(i+m/2)%2?b+1:a+1);
    for(I i=m/2;i<=m;i++)printf("%i ",(i+m/2)%2?c+1:a+1);
    printf("\n");
  }
}