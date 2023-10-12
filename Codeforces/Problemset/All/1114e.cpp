#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I A=1e9;
const I Q=60;
set<I>viss;
vector<I>sams;
I n;
I cnt=0;
I qry1(I i){
  printf("? %i\n",i+1),fflush(stdout),cnt++;
  I r;cin>>r;
  if(r==-1)exit(0);
  return r;
}
B qry2(I x){
  printf("> %i\n",x),fflush(stdout),cnt++;
  I r;cin>>r;
  if(r==-1)exit(0);
  return r;
}
void ans(I x,I d){
  printf("! %i %i\n",x,d),fflush(stdout),exit(0);
}
I fnd(){
  I l=n-1,r=A;
  while(l<r){
    I m=l+(r-l)/2;
    qry2(m)?l=m+1:r=m;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  mt19937 rnd(time(NULL));
  cin>>n;
  I y=fnd();
  while(cnt<Q&&sams.size()<n){
    I j;
    do{
      j=rnd()%n;
    }while(viss.find(j)!=viss.end());
    viss.insert(j),sams.push_back(qry1(j));
  }
  sort(sams.begin(),sams.end());
  I d=0;
  for(I i=0;i<sams.size();i++)for(I j=i+1;j<sams.size();j++)d=gcd(d,sams[j]-sams[i]);
  ans(y-(n-1)*d,d);
}