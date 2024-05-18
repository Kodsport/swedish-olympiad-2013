from sys import stdin
X=int(stdin.readline())
W=[1,1]
while(sum(W)<=X*1000): W.append(W[-1]+W[-2])
print len(W)-1
