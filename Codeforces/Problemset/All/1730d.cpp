#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I N=1e5;
C strs[2][N+1];
I cnts[26][26];
I main(){
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    cin>>strs[0];
    cin>>strs[1];
    reverse(strs[1],strs[1]+n);
    fill(&cnts[0][0],&cnts[0][0]+26*26,0);
    for(I i=0;i<n;i++){
      C a=strs[0][i],b=strs[1][i];
      if(a>b)swap(a,b);
      cnts[a-'a'][b-'a']++;
    }
    B res=1,one=1;
    for(I i=0;i<26;i++)for(I j=0;j<26;j++){
      if(cnts[i][j]%2){
        if(n%2){
          res&=one;
          res&=i==j;
          one=0;
        }else{
          res=0;
        }
      }
    }
    printf("%s\n",res?"YES":"NO");
  }
}