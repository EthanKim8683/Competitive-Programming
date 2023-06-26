#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
const I M=1e5;
pair<I,I>quns[M];
vector<I>majs[2*N+1];
vector<I>mins[2*N+1];
vector<I>rows[N+1];
vector<I>cols[N+1];
I ress[8+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I r,c;cin>>r>>c;
    quns[i]={r,c};
  }
  for(I i=0;i<m;i++){
    auto[row,col]=quns[i];
    I maj=row+col,min=n+row-col;
    majs[maj].push_back(min);
    mins[min].push_back(maj);
    rows[row].push_back(col);
    cols[col].push_back(row);
  }
  for(I i=0;i<=2*n;i++){
    sort(majs[i].begin(),majs[i].end());
    sort(mins[i].begin(),mins[i].end());
  }
  for(I i=0;i<=n;i++){
    sort(rows[i].begin(),rows[i].end());
    sort(cols[i].begin(),cols[i].end());
  }
  for(I i=0;i<m;i++){
    auto[row,col]=quns[i];
    I maj=row+col,min=n+row-col,cur=0;
    cur+=lower_bound(majs[maj].begin(),majs[maj].end(),min)!=majs[maj].begin();
    cur+=upper_bound(majs[maj].begin(),majs[maj].end(),min)!=majs[maj].end();
    cur+=lower_bound(mins[min].begin(),mins[min].end(),maj)!=mins[min].begin();
    cur+=upper_bound(mins[min].begin(),mins[min].end(),maj)!=mins[min].end();
    cur+=lower_bound(rows[row].begin(),rows[row].end(),col)!=rows[row].begin();
    cur+=upper_bound(rows[row].begin(),rows[row].end(),col)!=rows[row].end();
    cur+=lower_bound(cols[col].begin(),cols[col].end(),row)!=cols[col].begin();
    cur+=upper_bound(cols[col].begin(),cols[col].end(),row)!=cols[col].end();
    ress[cur]++;
  }
  for(I i=0;i<=8;i++)printf("%i ",ress[i]);
}