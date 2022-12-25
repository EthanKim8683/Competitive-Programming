#include<iostream>
#include<cstdio>
#include<deque>
#include<tuple>

using namespace std;

using I=int;

const I M=1000;
const I N=1000;
const I MAX=1e9;

I cels[N][M];
I ps[N+1][M+1];
tuple<I,I,I> chms[N][M];
tuple<I,I,I> mins1[N][M];
tuple<I,I,I> mins2[N][M];
deque<pair<tuple<I,I,I>,I>>que1;
I m,n,a,b,c,d;
I cnt1=0,cnt2=0;

void bld1(){
  for(I i=1;i<=n;i++)for(I j=1;j<=m;j++)
    ps[i][j]=cels[i-1][j-1]+ps[i-1][j]+ps[i][j-1]-ps[i-1][j-1];
}

I rng(I i,I j,I k,I l){
  return ps[k][l]-ps[k][j]-ps[i][l]+ps[i][j];
}

void clr1(){
  que1.clear();
  cnt1=cnt2=0;
}

void add1(tuple<I,I,I> val){
  while(que1.size()&&get<0>(que1.back().first)>get<0>(val))que1.pop_back();
  que1.push_back({val,cnt1++});
}

void rem1(){
  if(que1.size()&&que1.front().second==cnt2)que1.pop_front();
  cnt2++;
}

tuple<I,I,I> qry1(){
  return que1.front().first;
}

void bld2(){
  for(I i=0;i<n;i++){
    clr1();
    for(I j=0;j<a-c-1;j++)add1(chms[i][j]);
    mins1[i][0]=qry1();
    for(I j=0;j+a-c-1<m;j++){
      add1(chms[i][j+a-c-1]),rem1();
      mins1[i][j+1]=qry1();
    }
  }
  for(I i=0;i<m;i++){
    clr1();
    for(I j=0;j<b-d-1;j++)add1(mins1[j][i]);
    mins2[0][i]=qry1();
    for(I j=0;j+b-d-1<n;j++){
      add1(mins1[j+b-d-1][i]),rem1();
      mins2[j+1][i]=qry1();
    }
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>m>>n>>a>>b>>c>>d;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>cels[i][j];
  bld1();
  for(I i=0;i+d<=n;i++)for(I j=0;j+c<=m;j++)
    chms[i][j]={rng(i,j,i+d,j+c),i,j};
  bld2();
  I rsum=0,ri,rj,rk,rl;
  for(I i=0;i+b<=n;i++)for(I j=0;j+a<=m;j++){
    auto[sum,k,l]=mins2[i+1][j+1];
    sum=rng(i,j,i+b,j+a)-sum;
    if(sum>rsum)rsum=sum,ri=i,rj=j,rk=k,rl=l;
  }
  printf("%i %i\n%i %i\n",rj+1,ri+1,rl+1,rk+1);
  return 0;
}