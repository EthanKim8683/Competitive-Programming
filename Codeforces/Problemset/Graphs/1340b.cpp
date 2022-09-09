#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;
using C=char;

const I N=2000;
const I K=2000;
const I MAX=1e9;

I seqs[]{
  0b1110111,0b0010010,0b1011101,
  0b1011011,0b0111010,0b1101011,
  0b1101111,0b1010010,0b1111111,
  0b1111011
};
C cels[N][7];
I csts[N][10];
I bits[N];
queue<pair<I,I>>que;
B viss[N+1][K+1];
I movs[N+1][K+1];
I dgts[N+1][K+1];
vector<I>ress;
I n;

void add(I i,I j,I l,I m){
  j-=l;
  if(i>n||j<0||viss[i][j])return;
  viss[i][j]=1;
  movs[i][j]=l,dgts[i][j]=m;
  que.push({i,j});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++)for(I j=0;j<7;j++)
    bits[i]|=(cels[i][6-j]=='1')<<j;
  for(I i=0;i<n;i++)for(I j=0;j<10;j++){
    I bit=bits[i],seq=seqs[j];
    if((seq&bit)!=bit)csts[i][j]=MAX;
    else csts[i][j]=__builtin_popcount(seq^bit);
  }
  add(0,k,0,0);
  while(que.size()){
    auto[i,j]=que.front();que.pop();
    if(i==n&&j==0){
      while(i!=0){
        ress.push_back(dgts[i][j]);
        j+=movs[i][j],i-=1;
      }
      while(ress.size()){
        printf("%i",ress.back());
        ress.pop_back();
      }
      return 0;
    }
    for(I k=9;k>=0;k--)
      add(i+1,j,csts[i][k],k);
  }
  printf("-1\n");
  return 0;
}