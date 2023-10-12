#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=1<<16;
I ress[N];
I n;
I ask(S s,I i,I j){
  printf("%s %i %i\n",s.c_str(),i+1,j+1),fflush(stdout);
  I res;cin>>res;
  if(res==-1)exit(0);
  return res;
}
void ans(){
  printf("! ");
  for(I i=0;i<n;i++)printf("%i ",ress[i]);
  printf("\n"),fflush(stdout);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  I a1=ask("AND",0,1),o1=ask("OR",0,1);
  I a2=ask("AND",0,2),o2=ask("OR",0,2);
  I a3=ask("AND",1,2);
  ress[0]=(((a1^o1)&(a2^o2)^a3)|a1|a2)&o1&o2;
  ress[1]=ress[0]^a1^o1;
  ress[2]=ress[0]^a2^o2;
  for(I i=3;i<n;i++)ress[i]=ress[0]^ask("XOR",0,i);
  ans();
}