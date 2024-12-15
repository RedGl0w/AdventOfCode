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

def pushCrate(coo, direction, warehouse):
  nextCrate = nextFromDirection(coo, direction)
  match warehouse[nextCrate[0]][nextCrate[1]]:
    case 'O':
      # Try to move the crate after this one in the correct direction
      if not pushCrate(nextCrate, direction, warehouse):
        return False
    case '#':
      return False
  # Let's move the crate
  warehouse[nextCrate[0]][nextCrate[1]] = 'O'
  warehouse[coo[0]][coo[1]] = '.'
  return True

def simulateStep(coo, direction, warehouse):
  nextPosition = nextFromDirection(coo, direction)
  match warehouse[nextPosition[0]][nextPosition[1]]:
    case 'O':
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
      if c == 'O':
        total += 100*i+j
  return total


def main():
  warehouse, coo, movements = loadFile("input.txt")
  printWarehouse(warehouse, coo)
  for m in movements:
    coo = simulateStep(coo, m, warehouse)
    # print(f"-------- Dir : {m}")
    # printWarehouse(warehouse, coo)
  print(f"GPS total = {GPSSum(warehouse)}")

if __name__ == "__main__":
  main()
