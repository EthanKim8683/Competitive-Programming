#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e6;
const I A=4;
const I MAX=1e9;
I a_arr[N];
I cnts[A+1];
I tmps1[A+1],tmps2[A+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cnts[a_arr[i]]++;
  I tot=0;
  for(I i=0;i<=A;i++)tot+=cnts[i]*i;
  I res=MAX;
  for(I i=0;i<=tot/3;i++){
    I j=tot-i*3;
    if(j%4!=0)continue;
    j/=4;
    copy_n(cnts,A+1,tmps1);
    tmps2[0]=n-i-j,tmps2[3]=i,tmps2[4]=j;
    I cur=0;
    for(I k=0,l=0;k<=A||l<=A;){
      I dif=min(tmps1[k],tmps2[l]);
      tmps1[k]-=dif,tmps2[l]-=dif;
      cur+=max((k-l)*dif,0);
      k+=tmps1[k]==0,l+=tmps2[l]==0;
    }
    res=min(res,cur);
  }
  printf("%i\n",res==MAX?-1:res);
}
/*
since the final seating must contain only compartments with three or four
students, we can count and take the minimum of the number of moves required to
produce each combination of three and four student compartments
*/