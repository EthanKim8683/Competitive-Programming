#include<bits/stdc++.h>

using namespace std;

using I=int;

const I X=7;

I facs[X+1];
I prms[X];

I cnv(I*ptr,I len){
  I res=0;
  for(I i=0;i<len;i++)res=res*7+ptr[i];
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=X;i++)facs[i]=facs[i-1]*i;
  I n,m;cin>>n>>m,n--,m--;
  I nln=1,mln=1,len=2;
  for(I i=n;i/=X;)nln++,len++;
  for(I i=m;i/=X;)mln++,len++;
  if(len>X)printf("0\n"),exit(0);
  iota(prms,prms+X,0);
  I res=0;
  do
    res+=cnv(prms,nln)<=n&&cnv(prms+nln,mln)<=m;
  while(next_permutation(prms,prms+X));
  printf("%i\n",res/facs[X-len]);
}