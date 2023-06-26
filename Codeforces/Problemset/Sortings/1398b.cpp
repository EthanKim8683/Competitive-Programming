#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
vector<I>lens;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    lens.clear();
    I len=1;
    for(I i=1;i<n;i++){
      if(s[i]==s[i-1]){
        len++;
      }else{
        if(s[i-1]=='1')lens.push_back(len);
        len=1;
      }
    }
    if(s[n-1]=='1')lens.push_back(len);
    sort(lens.begin(),lens.end());
    I res=0;
    for(I i=lens.size()-1;i>=0;i-=2)res+=lens[i];
    printf("%i\n",res);
  }
}