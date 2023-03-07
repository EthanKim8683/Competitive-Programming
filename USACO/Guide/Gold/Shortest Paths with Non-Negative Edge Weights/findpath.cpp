#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1000;
const Lli MAX=1e18;
tuple<I,I,I,I>dees[N];
map<I,array<vector<I>,4>>evts1,evts2;
vector<I>edgs[N][4];
map<I,I>curs;
map<pair<I,I>,vector<pair<pair<I,I>,I>>>adjs;
priority_queue<pair<Lli,pair<I,I>>>ques;
map<pair<I,I>,Lli>diss;
void edg(pair<I,I>a,pair<I,I>b,I d){
  if(a==b)return;
  adjs[a].push_back({b,d});
  adjs[b].push_back({a,d});
}
void add(pair<I,I>a,Lli dis){
  if(!diss.count(a))diss[a]=MAX;
  if(dis>=diss[a])return;
  ques.push({-(diss[a]=dis),a});
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
    evts1.clear(),evts2.clear();
    evts1[y1][2].push_back(x1);
    evts1[y2][3].push_back(x2);
    evts2[x1][2].push_back(y1);
    evts2[x2][3].push_back(y2);
    I n;cin>>n;
    B vld=1;
    for(I i=0;i<n;i++){
      I x3,y3,x4,y4;cin>>x3>>y3>>x4>>y4;
      if(x3>x4)swap(x3,x4);
      if(y3>y4)swap(y3,y4);
      dees[i]={x3,y3,x4,y4};
      evts1[y3][0].push_back(i);
      evts1[y4][1].push_back(i);
      evts2[x3][0].push_back(i);
      evts2[x4][1].push_back(i);
      vld&=x1<=x3||x1>=x4||y1<=y3||y1>=y4;
      vld&=x2<=x3||x2>=x4||y2<=y3||y2>=y4;
    }
    if(!vld){printf("No Path\n");continue;}
    if(x1==x2){
      B vld=1;
      for(I i=0;i<n;i++){
        auto[x3,y3,x4,y4]=dees[i];
        vld&=x3>=x1||x4<=x1||y3>=max(y1,y2)||y4<=min(y1,y2);
      }
      if(vld){printf("%i\n",abs(y1-y2));continue;}
    }
    if(y1==y2){
      B vld=1;
      for(I i=0;i<n;i++){
        auto[x3,y3,x4,y4]=dees[i];
        vld&=y3>=y1||y4<=y1||x3>=max(x1,x2)||x4<=min(x1,x2);
      }
      if(vld){printf("%i\n",abs(x1-x2));continue;}
    }
    for(I i=0;i<n;i++)for(I j=0;j<4;j++)edgs[i][j].clear();
    adjs.clear();
    diss.clear();
    for(auto&[y,hnds]:evts1){
      for(auto i:hnds[0]){
        auto[x1,y1,x2,y2]=dees[i];
        curs[x1]=i;
        curs[x2]=i;
      }
      for(I i=0;i<2;i++){
        for(auto j:hnds[i]){
          auto[x1,y1,x2,y2]=dees[j];
          if(curs.empty())continue;
          auto low=curs.lower_bound(x1);
          auto upp=curs.upper_bound(x2);
          if(low--!=curs.begin()){
            I k=low->second;
            auto[x3,y3,x4,y4]=dees[k];
            edgs[k][1].push_back(y);
            edg({x4,y},{x1,y},abs(x4-x1));
          }
          if(upp!=curs.end()){
            I k=upp->second;
            auto[x3,y3,x4,y4]=dees[k];
            edgs[k][0].push_back(y);
            edg({x3,y},{x2,y},abs(x3-x2));
          }
        }
      }
      for(I i=0;i<2;i++){
        for(auto x:hnds[2+i]){
          if(curs.empty())continue;
          auto low=curs.upper_bound(x);
          auto upp=curs.lower_bound(x);
          if(low--!=curs.begin()){
            I j=low->second;
            auto[x1,y1,x2,y2]=dees[j];
            edgs[j][1].push_back(y);
            edg({x,y},{x2,y},abs(x-x2));
          }
          if(upp!=curs.end()){
            I j=upp->second;
            auto[x1,y1,x2,y2]=dees[j];
            edgs[j][0].push_back(y);
            edg({x,y},{x1,y},abs(x-x1));
          }
        }
      }
      for(auto i:hnds[1]){
        auto[x1,y1,x2,y2]=dees[i];
        curs.erase(x1);
        curs.erase(x2);
      }
    }
    for(auto&[x,hnds]:evts2){
      for(auto i:hnds[0]){
        auto[x1,y1,x2,y2]=dees[i];
        curs[y1]=i;
        curs[y2]=i;
      }
      for(I i=0;i<2;i++){
        for(auto j:hnds[i]){
          auto[x1,y1,x2,y2]=dees[j];
          if(curs.empty())continue;
          auto low=curs.lower_bound(y1);
          auto upp=curs.upper_bound(y2);
          if(low--!=curs.begin()){
            I k=low->second;
            auto[x3,y3,x4,y4]=dees[k];
            edgs[k][3].push_back(x);
            edg({x,y4},{x,y1},abs(y4-y1));
          }
          if(upp!=curs.end()){
            I k=upp->second;
            auto[x3,y3,x4,y4]=dees[k];
            edgs[k][2].push_back(x);
            edg({x,y3},{x,y2},abs(y3-y2));
          }
        }
      }
      for(I i=0;i<2;i++){
        for(auto y:hnds[2+i]){
          if(curs.empty())continue;
          auto low=curs.upper_bound(y);
          auto upp=curs.lower_bound(y);
          if(low--!=curs.begin()){
            I j=low->second;
            auto[x1,y1,x2,y2]=dees[j];
            edgs[j][3].push_back(x);
            edg({x,y},{x,y2},abs(y-y2));
          }
          if(upp!=curs.end()){
            I j=upp->second;
            auto[x1,y1,x2,y2]=dees[j];
            edgs[j][2].push_back(x);
            edg({x,y},{x,y1},abs(y-y1));
          }
        }
      }
      for(auto i:hnds[1]){
        auto[x1,y1,x2,y2]=dees[i];
        curs.erase(y1);
        curs.erase(y2);
      }
    }
    for(I i=0;i<n;i++){
      auto[x1,y1,x2,y2]=dees[i];
      edgs[i][0].push_back(y1);
      edgs[i][0].push_back(y2);
      sort(edgs[i][0].begin(),edgs[i][0].end());
      for(I j=0;j+1<edgs[i][0].size();j++){
        I y3=edgs[i][0][j],y4=edgs[i][0][j+1];
        edg({x1,y3},{x1,y4},abs(y3-y4));
      }
      edgs[i][1].push_back(y1);
      edgs[i][1].push_back(y2);
      sort(edgs[i][1].begin(),edgs[i][1].end());
      for(I j=0;j+1<edgs[i][1].size();j++){
        I y3=edgs[i][1][j],y4=edgs[i][1][j+1];
        edg({x2,y3},{x2,y4},abs(y3-y4));
      }
      edgs[i][2].push_back(x1);
      edgs[i][2].push_back(x2);
      sort(edgs[i][2].begin(),edgs[i][2].end());
      for(I j=0;j+1<edgs[i][2].size();j++){
        I x3=edgs[i][2][j],x4=edgs[i][2][j+1];
        edg({x3,y1},{x4,y1},abs(x3-x4));
      }
      edgs[i][3].push_back(x1);
      edgs[i][3].push_back(x2);
      sort(edgs[i][3].begin(),edgs[i][3].end());
      for(I j=0;j+1<edgs[i][3].size();j++){
        I x3=edgs[i][3][j],x4=edgs[i][3][j+1];
        edg({x3,y2},{x4,y2},abs(x3-x4));
      }
    }
    add({x1,y1},0);
    while(ques.size()){
      auto[dis,a]=ques.top();ques.pop();
      if((dis=-dis)!=diss[a])continue;
      for(auto[b,d]:adjs[a])add(b,dis+d);
    }
    if(!diss.count({x2,y2})){printf("No Path\n");continue;}
    printf("%lli\n",diss[{x2,y2}]);
  }
}