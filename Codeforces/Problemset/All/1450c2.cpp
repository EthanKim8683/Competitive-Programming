#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I N=300;
C cels[N][N+1];
C tmps[N][N+1];
I prms1[3],prms2[3];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>cels[i];
    B fnd=0;
    iota(prms1,prms1+3,0);
    do{
      iota(prms2,prms2+3,0);
      do{
        B vld=1;
        for(I i=0;i<3;i++)vld&=prms1[i]!=prms2[i];
        if(!vld)continue;
        I cnt=0,tot=0;
        for(I i=0;i<n;i++)for(I j=0;j<n;j++){
          tmps[i][j]=cels[i][j];
          if(cels[i][j]=='X')if(j%3==prms1[i%3])tmps[i][j]='O',cnt++;
          if(cels[i][j]=='O')if(j%3==prms2[i%3])tmps[i][j]='X',cnt++;
          if(cels[i][j]!='.')tot++;
        }
        fnd=cnt<=tot/3;
      }while(!fnd&&next_permutation(prms2,prms2+3));
    }while(!fnd&&next_permutation(prms1,prms1+3));
    for(I i=0;i<n;i++)tmps[i][n]=0,printf("%s\n",tmps[i]);
  }
}
/*
observe that any 3-by-3 permutation matrix contains 3 1's out of 9 cells, and
when tiled, always produces a draw

if we choose a tiling for all X and all O, the problem can be solved
very easily

however, if we choose two tilings such that it is possible to choose cells
from either one to produce a winning configuration, the tiling pair is
invalid

we can check this by maximimizng the number of O cells, checking for a win,
then maximimizing the number of X cells and checking for a win

the easiest observation is that tilings which have X's in the same cells and
O's in the same cells satisfy the property above, as maximizing the O cells
results in the O matrix and maximizing the X cells results in the X matrix

we can check all possible tiling pairs in 3! * 3! iterations to ensure at
most floor(k / 3) operations are used, since if one tiling uses more than
floor(k / 3) operations, there must be a tiling that uses fewer than that
*/