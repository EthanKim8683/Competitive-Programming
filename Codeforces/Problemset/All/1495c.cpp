#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I N=500;
const I M=500;
C tabs[N][M+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>tabs[i];
    I off=n%3==0?2:0;
    for(I i=0;i<n;i++)if((i+off)%3==0){
      for(I j=0;j<m;j++)tabs[i][j]='X';
      if(i+2<n)for(I j=0;j<m;j++)if((j-1<0||(tabs[i+1][j-1]=='.'&&tabs[i+2][j-1]=='.'))&&(j+1>=m||(tabs[i+1][j+1]=='.'&&tabs[i+2][j+1]=='.'))){tabs[i+1][j]=tabs[i+2][j]='X';break;}
    }
    for(I i=0;i<n;i++)printf("%s\n",tabs[i]);
  }
}
/*
since no two empty cells may have common points, if we fill every third row
(with offset to handle an edge case) with empty cells, we end up with
straight paths of empty cells with single-cell "stubs"

all paths are guaranteed to be simple paths since no 4-by-4 (or greater) empty
cell "groups" can exist, as that would require two empty cells to be
neighboring to begin with, and no filled row can reach another filled row for
the same reason

then, we can join the rows such that no 4-by-4 (or greater) groups are formed
to complete the tree
*/