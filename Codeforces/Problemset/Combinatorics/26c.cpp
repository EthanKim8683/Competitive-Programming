#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
const I M=100;
vector<I>curs;
I ress[N][M];
I n,m;
void fil(I x,I y,I w,I h){
  curs.clear();
  if(x-1>=0)for(I i=y;i<y+h;i++)curs.push_back(ress[x-1][i]);
  if(y-1>=0)for(I i=x;i<x+w;i++)curs.push_back(ress[i][y-1]);
  if(x+w<n)for(I i=y;i<y+h;i++)curs.push_back(ress[x+w][i]);
  if(y+h<m)for(I i=x;i<x+w;i++)curs.push_back(ress[i][y+h]);
  sort(curs.begin(),curs.end());
  I mex=0;
  for(auto i:curs)if(mex==i)mex++;
  for(I i=x;i<x+w;i++)for(I j=y;j<y+h;j++)ress[i][j]=mex;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&ress[0][0],&ress[0][0]+N*M,-1);
  I a,b,c;cin>>n>>m>>a>>b>>c;
  if(n*m%2==1)printf("IMPOSSIBLE"),exit(0);
  if(n%2==1){
    for(I i=0;i<m;i+=2){
      if(a==0)printf("IMPOSSIBLE"),exit(0);
      a--,fil(n-1,i,1,2);
    }
  }
  if(m%2==1){
    for(I i=0;i<n;i+=2){
      if(b==0)printf("IMPOSSIBLE"),exit(0);
      b--,fil(i,m-1,2,1);
    }
  }
  for(I i=0;i<n/2*2;i+=2)for(I j=0;j<m/2*2;j+=2){
    if(c>=1){
      c--,fil(i,j,2,2);
      continue;
    }
    if(a>=2){
      a-=2,fil(i,j,1,2),fil(i+1,j,1,2);
      continue;
    }
    if(b>=2){
      b-=2,fil(i,j,2,1),fil(i,j+1,2,1);
      continue;
    }
    printf("IMPOSSIBLE"),exit(0);
  }
  for(I i=0;i<n;i++){
    for(I j=0;j<m;j++)printf("%c",ress[i][j]+'a');
    printf("\n");
  }
}
/*
if the length is odd and the width is even, we must tile a 1-by-m strip using
1-by-2 planks

if the length is even and the width is odd, we must tile a n-by-1 strip using
2-by-1 planks

if both the length and width are odd, a 1-by-1 space would remain impossible
to fill (each plank covers an even number of tiles, odd-by-odd means an odd
total)

the remaining space can be greedily filled with 2-by-2 planks and whatever's
left over can be delegated to pairs of 1-by-2 or 2-by-1 planks
*/