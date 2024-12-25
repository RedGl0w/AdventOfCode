from copy import copy

with open("input.txt", "r", encoding="utf-8") as f:
  edges = {}
  vertices = []

  for line in f:
    line = line.strip()
    if line == "":
      continue
    a,b = line.split("-")
    def addEdges(x,y):
      if x not in edges:
        edges[x] = []
      edges[x].append(y)
      if x not in vertices:
        vertices.append(x)
    addEdges(a,b)
    addEdges(b,a)
  
  largest = []
  def backTrack(previous, previousIndex = -1):
    global largest
    if len(previous) > len(largest):
      largest = copy(previous)
    for idx, vertex in enumerate(vertices[previousIndex+1:]):
      for k in previous:
        if k not in edges[vertex]:
          break
      else:
        previous.append(vertex)
        backTrack(previous, idx)
        previous.pop()
  backTrack([])
  print(",".join(sorted(largest)))

    
