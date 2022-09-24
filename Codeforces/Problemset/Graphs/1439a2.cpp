#include<iostream>
#include<cstdio>
#include<vector>
#include<tuple>

using namespace std;

using I=int;
using C=char;

const I N=100;
const I M=100;

I movs1[]{
  0b0000,0b1011,0b0111,0b1100,
  0b1101,0b0110,0b1010,0b0001,
  0b1110,0b0101,0b1001,0b0010,
  0b0011,0b1000,0b0100,0b1111
};
I movs2[]{
  0b0000,0b0010,0b0001,0b1000
};
I movs3[]{
  0b0000,0b0010,0b1000,0b0001
};
I movs4[]{
  0b0000,0b0110
};
tuple<I,I,I,I,I,I>cnvs[]{
  {0,0,0,1,1,1},{0,0,0,1,1,0},
  {0,1,1,0,1,1},{0,0,1,0,1,1}
};
C cels[N][M+1];
vector<tuple<I,I,I,I,I,I>>ress;

I cps1(I i,I j){
  return cels[i+0][j+0]<<0|cels[i+0][j+1]<<1|
         cels[i+1][j+0]<<3|cels[i+1][j+1]<<2;
}

I cps2(I i,I j){
  return cels[i+0][j+0]<<0|cels[i+0][j+1]<<1;
}

I cps3(I i,I j){
  return cels[i+0][j+0]<<0|cels[i+1][j+0]<<1;
}

I cps4(I i,I j){
  return cels[i+0][j+0];
}

void add(I i,I j,I msk){
  for(I k=0;k<4;k++){
    if(msk>>k&1){
      I a=i+get<0>(cnvs[k]),b=j+get<1>(cnvs[k]);
      I c=i+get<2>(cnvs[k]),d=j+get<3>(cnvs[k]);
      I e=i+get<4>(cnvs[k]),f=j+get<5>(cnvs[k]);
      ress.push_back({a,b,c,d,e,f});
      cels[a][b]^=1,cels[c][d]^=1,cels[e][f]^=1;
    }
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>cels[i];
    for(I i=0;i<n;i++)for(I j=0;j<m;j++)
      cels[i][j]=cels[i][j]=='1';
    ress.clear();
    if(n&1)for(I i=0;i<(m&~1);i+=2)add(n-2,i,movs2[cps2(n-1,i)]);
    if(m&1)for(I i=0;i<(n&~1);i+=2)add(i,m-2,movs3[cps3(i,m-1)]);
    if(n&1&&m&1)add(n-2,m-2,movs4[cps4(n-1,m-1)]);
    for(I i=0;i<(n&~1);i+=2)for(I j=0;j<(m&~1);j+=2)add(i,j,movs1[cps1(i,j)]);
    printf("%i\n",ress.size());
    for(auto[a,b,c,d,e,f]:ress)
      printf("%i %i %i %i %i %i\n",a+1,b+1,c+1,d+1,e+1,f+1);
  }
  return 0;
}