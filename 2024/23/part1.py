with open("input.txt", "r", encoding="utf-8") as f:
  edges = {}

  for line in f:
    line = line.strip()
    if line == "":
      continue
    a,b = line.split("-")
    def addEdges(x,y):
      if x not in edges:
        edges[x] = []
      edges[x].append(y)
    addEdges(a,b)
    addEdges(b,a)
  
  alreadySeen = set()
  def backTrack(previous):
    if len(previous) == 3:
      startsWithT = bool(sum(map(lambda k: k[0] == "t", previous)))
      if startsWithT:
        alreadySeen.add(frozenset(previous))
      return
    for vertex in edges:
      if vertex in previous:
        continue
      isntNeighbour = bool(sum(map(lambda k: k not in edges[vertex], previous)))
      if isntNeighbour:
        continue
      previous.add(vertex)
      backTrack(previous)
      previous.remove(vertex)
  
  backTrack(set())
  print(len(alreadySeen))

    
