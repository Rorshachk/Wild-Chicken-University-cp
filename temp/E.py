import sys
input = sys.stdin.readline
n,m,p = [int(x) for x in input().split()]
a = [int(x) for x in input().split()]
b = [int(x) for x in input().split()]
li = []
for o in a:
    for q in b:
        li.append(q / o)
li.sort()
good = True
for idx in range(len(li) - 1):
    if li[idx + 1] > li[idx] * (1 + p / 100):
        good = False 
        break
if good:
    print("Ride on!")
else:
    print("Time to change gears!")
