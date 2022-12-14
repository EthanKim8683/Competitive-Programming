#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I N=1e5;
C cels[N+1];
vector<I>asts;
vector<I>pacs;
I n;
I m,k;
I dis(I a,I b,I c){
  a=asts[a],b=asts[b],c=pacs[c];
  return abs(b-a)+min(abs(c-a),abs(b-c));
}
B chk(I x){
  I j=0;
  for(I i=0;i<m&&j<k;i++){
    I l=j;
    while(l<k&&dis(j,l,i)<=x)l++;
    j=l;
  }
  return j==k;
}
I fnd(){
  I l=0,r=2*n;
  while(l<r){
    I m=l+(r-l)/2;
    chk(m)?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  cin>>cels;
  for(I i=0;i<n;i++)if(cels[i]=='P')pacs.push_back(i);
  for(I i=0;i<n;i++)if(cels[i]=='*')asts.push_back(i);
  m=pacs.size(),k=asts.size();
  printf("%i\n",fnd());
}