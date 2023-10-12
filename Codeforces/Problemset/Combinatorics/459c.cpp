#include<bits/stdc++.h>
using namespace std;
using I=int;
const I D=1000;
const I N=1000;
I ress[D][N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k,d;cin>>n>>k>>d;
  for(I i=1;i<n;i++){
    I sum=ress[0][i-1]+1,car=0;
    ress[0][i]=sum%k,car=sum/k;
    for(I j=1;j<d;j++){
      sum=ress[j][i-1]+car;
      ress[j][i]=sum%k,car=sum/k;
    }
    if(car>0)printf("-1"),exit(0);
  }
  for(I i=0;i<d;i++){
    for(I j=0;j<n;j++)printf("%i ",ress[i][j]+1);
    printf("\n");
  }
}
/*
we can think of the problem as assigning each student a unique d-digit number
of base k

this means that if n exceeds k ^ d, there is no valid arrangement

otherwise, we can simply increment the number for each student
*/