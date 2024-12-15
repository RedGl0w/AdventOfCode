def loadFile(filename):
  warehouse, coo, movements = [], (0,0), []
  isMap = True
  with open(filename, 'r', encoding='utf-8') as f:
    for i, line in enumerate(f):
      line = line.strip()
      if line == "":
        isMap = False
      elif isMap:
        r = []
        for j, c in enumerate(line):
          if c == '@':
            coo = (i,j)
            r.append('.')
          else:
            r.append(c)
        warehouse.append(r)
      else:
        movements.extend(list(line))
  return warehouse, coo, movements

def scaleUp(warehouse, coo):
  newWarehouse = []
  for l in warehouse:
    line = []
    for c in l:
      if c == 'O':
        line.extend(['[',']'])
      else:
        line.extend([c,c])
    newWarehouse.append(line)
  return newWarehouse, (coo[0], coo[1]*2)


def nextFromDirection(coo, direction):
  i,j = coo
  match direction:
    case '<':
      return (i, j-1)
    case '>':
      return (i, j+1)
    case '^':
      return (i-1, j)
    case 'v':
      return (i+1, j)
    
def otherExtremity(coo, warehouse):
  c = warehouse[coo[0]][coo[1]]
  return (coo[0], coo[1]+1) if c == '[' else (coo[0], coo[1]-1)

# We have to specify a function to check if we can push the box because on
# one side of the box we could be able to push, but if the other part can't move,
# if we moved the first part we would have problem (need to rollback ?)
def canPush(coo, direction, warehouse, shouldCallOther = True):
  c = warehouse[coo[0]][coo[1]]
  match c:
    case '[' | ']':
      otherBox = otherExtremity(coo, warehouse)
      if shouldCallOther and (not canPush(otherBox, direction, warehouse, False)):
        return False
      return canPush(nextFromDirection(coo, direction), direction, warehouse)
    case '#':
      return False
  return True
      

def pushCrate(coo, direction, warehouse, shouldCallOther = True):
  nextCrate = nextFromDirection(coo, direction)
  # We start by checking if box extremities of the box in case of a vertical movement
  # are able to be pushed, and if it is possible, we move the other extremity
  # and later we move the part of the box at coo
  if shouldCallOther and (direction in ('^', 'v')):
    otherBox = otherExtremity(coo, warehouse)
    if not canPush(otherBox, direction, warehouse):
      return False
    if not canPush(coo, direction, warehouse):
      return False
    assert pushCrate(otherBox, direction, warehouse, False)
  match warehouse[nextCrate[0]][nextCrate[1]]:
    case '[' | ']':
      # Try to move the crate after this one in the correct direction
      if not pushCrate(nextCrate, direction, warehouse):
        return False
    case '#':
      return False
  # Let's move the crate
  warehouse[nextCrate[0]][nextCrate[1]] = warehouse[coo[0]][coo[1]]
  warehouse[coo[0]][coo[1]] = '.'
  return True

def simulateStep(coo, direction, warehouse):
  nextPosition = nextFromDirection(coo, direction)
  match warehouse[nextPosition[0]][nextPosition[1]]:
    case '[' | ']':
      if pushCrate(nextPosition, direction, warehouse):
        return nextPosition
      return coo
    case '#':
      return coo
    case '.':
      return nextPosition
    case _:
      assert False, f"Unexpected {warehouse[nextPosition[0]][nextPosition[1]]}"

def printWarehouse(warehouse, coo):
  for i, l in enumerate(warehouse):
    line = ""
    if i == coo[0]:
      assert l[coo[1]] == '.'
      l[coo[1]] = '@'
      line = "".join(l)
      l[coo[1]] = '.'
    else:
      line = "".join(l)
    print(line)

def GPSSum(warehouse):
  total = 0
  for i, l in enumerate(warehouse):
    for j, c in enumerate(l):
      if c == '[':
        total += 100*i+j
  return total


def main():
  warehouse, coo, movements = loadFile("input.txt")
  warehouse, coo = scaleUp(warehouse, coo)
  for m in movements:
    coo = simulateStep(coo, m, warehouse)
    # print(f"-------- Dir : {m}")
    # printWarehouse(warehouse, coo)
  print(f"GPS total = {GPSSum(warehouse)}")

if __name__ == "__main__":
  main()
