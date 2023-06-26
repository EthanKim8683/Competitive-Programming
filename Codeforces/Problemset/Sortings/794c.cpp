#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
deque<C>ques1,ques2;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  S t;cin>>t;
  I n=s.size();
  sort(s.begin(),s.end());
  sort(t.begin(),t.end());
  reverse(t.begin(),t.end());
  for(I i=0;i<n-n/2;i++)ques1.push_back(s[i]);
  for(I i=0;i<n/2;i++)ques2.push_back(t[i]);
  S low="",upp="";
  while(low.size()+upp.size()<n){
    if((low.size()+upp.size())%2){
      if(ques1.size()&&ques2.front()>ques1.front()){
        low+=S(1,ques2.front()),ques2.pop_front();
      }else{
        upp+=S(1,ques2.back()),ques2.pop_back();
      }
    }else{
      if(ques2.size()&&ques1.front()<ques2.front()){
        low+=S(1,ques1.front()),ques1.pop_front();
      }else{
        upp+=S(1,ques1.back()),ques1.pop_back();
      }
    }
  }
  reverse(upp.begin(),upp.end());
  printf("%s\n",(low+upp).c_str());
}