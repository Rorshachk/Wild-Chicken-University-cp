import sys
input = sys.stdin.readline
from heapq import heappush, heappop
N, S, T = [int(x) for x in input().split()]
# S -= 1
# T -= 1
edges = [0 for _ in range(N)]
for i in range(N):
    a = [int(x) for x in input().split()]
    edges[i] = a

h = [(0,S)]
l = [float('inf') for _ in range(N)]
visited = [False for _ in range(N)]
visited_count = 0
l[S] = 0
while h and visited_count < N:
    _, u = heappop(h)
    if visited[u]:
        continue
    visited[u] = True
    visited_count += 1
    for v in range(N):
        if not visited[v] and u != v and l[u] + edges[u][v] < l[v]:
            l[v] = l[u] + edges[u][v]
            heappush(h, (l[v], v))
print(l[T])

