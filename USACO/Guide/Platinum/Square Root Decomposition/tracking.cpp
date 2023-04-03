#include<iostream>
#include<stdio.h>
#include<math.h>
using namespace std;
using I=int;
const I MEM=5500;
const I MAX=1e9;
#ifdef ETHANKIM8683
I _mems[MEM];
I _n,_k;
I _i,_j;
void helpBessie(I c);
I get(I i){
  return _mems[i];
}
void set(I i,I val){
  _mems[i]=val;
}
void shoutMinimum(I i){
  printf("%i\n",i);
}
I getTrainLength(){
  return _n;
}
I getWindowLength(){
  return _k;
}
I getCurrentCarIndex(){
  return _i;
}
I getCurrentPassIndex(){
  return _j;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>_n>>_k;
  I c_arr[_n];
  for(I i=0;i<_n;i++)cin>>c_arr[i];
  for(_i=0,_j=0;_i<_n;_i++)helpBessie(c_arr[_i]);
  for(_i=0,_j=1;_i<_n;_i++)helpBessie(c_arr[_i]);
}
#else
#include"grader.h"
#endif
void pre(){
  I n=getTrainLength(),k=getWindowLength();
}
void pss1(I c){
  I n=getTrainLength(),k=getWindowLength();
  I i=getCurrentCarIndex();
}
void mid(){
  I n=getTrainLength(),k=getWindowLength();
}
void pss2(I c){
  I n=getTrainLength(),k=getWindowLength();
  I i=getCurrentCarIndex();
}
void pst(){
  I n=getTrainLength(),k=getWindowLength();
}
void helpBessie(I c){
  I n=getTrainLength();
  I i=getCurrentCarIndex(),j=getCurrentPassIndex();
  if(j==0&&i==0)pre();
  if(j==0)pss1(c);
  if(j==0&&i==n-1)mid();
  if(j==1)pss2(c);
  if(j==1&&i==n-1)pst();
}
/*
monotonic of

ends, ends, ends, begins, begins, begins

bbbkeebkeebbke

b  e
 b  e
  b  e
   b  e
    b  e
     b  e
   |-|

k=4
bbb     bb
  eee    eee
  3333   7777
   4444   8888
    5555   9999
1111    6666
 2222    7777
  3333

k at most n/k times

only keep c's after contiguous k begin and
before next begin

if k <= sqrt(n):
  sliding window

else:
  find k-intervals:
  if i - prev_min == k:
    k-interval begins at prev_min
    k-interval ends at i

  e's bs are non-overlapping with b's bs

  if c_arr[i] < cur and is_b_interval:
    cur = c_arr[i]

  for e's, use yet another sqrt decomp
  divide into blocks of sqrt(N) such that
    ends in the next block apply minimums
    to previous blocks
  querying end is just all next blocks
    plus current (at most sqrt(N)) data
    points
  
  first pass can find all k-intervals
    (process for b's)
*/