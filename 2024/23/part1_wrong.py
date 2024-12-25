with open("mockup.txt", "r", encoding="utf-8") as f:
  # The machines ids are lowercase 2 chars, it's easy to convert to an int
  def idtoint(s):
    assert len(s) == 2
    return (ord(s[0])-ord('a'))*26+(ord(s[1])-ord('a'))
  numberOfInt = idtoint('zz')+1

  # An optimized union-find where we save the size of
  # the equivalent class too and if there is a machine starting
  # with a t. It will be easy to count after it
  ranks = [0 for _ in range(numberOfInt)]
  parents = [i for i in range(numberOfInt)]
  startWithT = [False for _ in range(numberOfInt)]
  size = [1 for _ in range(numberOfInt)]

  def find(a):
    if parents[a] != a:
      parents[a] = find(parents[a])
    return parents[a]

  def union(a, b):
    aroot = find(a)
    broot = find(b)
    if aroot != broot:
      x = None
      y = None
      if ranks[aroot] < ranks[broot]:
        parents[aroot] = broot
        x = broot
        y = aroot
      else:
        parents[broot] = aroot
        x = aroot
        y = broot
        if ranks[aroot] == ranks[broot]:
          ranks[aroot] += 1
      startWithT[x] = startWithT[x] or startWithT[y]
      size[x] += size[y]
      size[y] = 0

  for line in f:
    line = line.strip()
    if line == "":
      continue
    a,b = line.split("-")
    inta,intb = idtoint(a), idtoint(b)
    if a[0] == "t":
      startWithT[find(inta)] = True
    if b[0] == "t":
      startWithT[find(intb)] = True
    union(inta, intb)
  
  print(parents)
  print(size)
  print(sum(size[i] == 3 and startWithT[i] for i in range(numberOfInt)))
