#include<iostream>
#include<cstdio>

using namespace std;

using I=int;

/*
0 3

There is a pattern here but I'm too lazy
to figure it out.
*/

const I P=17;

I ones1[P],ones2[P];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I l,r;cin>>l>>r;
    fill_n(ones1,P,0),fill_n(ones2,P,0);
    for(I i=l;i<=r;i++){
      I a;cin>>a;
      for(I j=0;j<P;j++)ones1[j]+=a>>j&1;
    }
    for(I i=l;i<=r;i++)
      for(I j=0;j<P;j++)ones2[j]+=i>>j&1;
    I res=0;
    for(I i=0;i<P;i++)
      res|=(ones1[i]!=ones2[i])<<i;
    printf("%i\n",res);
  }
  return 0;
}