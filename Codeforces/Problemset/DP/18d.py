N,X=5000,2000
lows,upps,viss=[-1]*(X+1),[-1]*(X+1),[0]*N
n=int(input())
for i in range(n):
  t,x=input().split()
  x=int(x)
  if t=="win" and upps[x]==-1:lows[x]=i
  if t=="sell":upps[x]=i
ress=[]
for i in range(X+1)[::-1]:
  l,r=lows[i],upps[i]
  if l==-1 or r==-1 or l>r:continue
  vis=0
  for j in range(l,r+1):vis|=viss[j]
  if vis:continue
  for j in range(l,r+1):viss[j]=1
  ress.append(i)
res,fac,cur=0,1,0
for x in ress[::-1]:
  while cur<x:fac*=2;cur+=1
  res+=fac
print(res)