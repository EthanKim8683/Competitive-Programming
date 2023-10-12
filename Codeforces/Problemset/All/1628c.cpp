#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1000;
I grds[N][N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)for(I j=0;j<n;j++)cin>>grds[i][j];
    I res=0;
    for(I i=0;i<n;i++)for(I j=0;j<n;j++){
      if(min(min(min(i,j),n-1-i),n-1-j)/2%2==0)res^=grds[i][j];
      if(i>j&&(i+j)%2==1&&i%2==1)res^=grds[i][j];
      if(i>n-1-j&&(i+j)%2==0&&i%2==1)res^=grds[i][j];
    }
    printf("%i\n",res);
  }
}
/*
if we take the xor sum of entire provided grid, all a[i][j] on the outside
layer of the grid, excluding the corners, are represented

we can do this repeatedly for each layer of the grid until we have a region
consisting of two diagonals of unrepresented cells, one from the top left to
bottom right, and the other from the top right to the bottom left

we can find the value of this region by taking the xor-sum of the diagonals
individually, since they do not overlap

to represent a diagonal, we can follow this "sparse checkerboard" pattern
in the shape of a triangle
*/