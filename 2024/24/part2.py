import itertools

NUMBER_OF_SWITCH = 4

with open("mockup.txt", "r", encoding="utf-8") as f:
  
  initial = {}
  gates = {}

  x = set()
  y = set()
  z = set()

  def addValues(wire):
    match wire[0]:
      case 'x':
        x.add(wire)
      case 'y':
        y.add(wire)
      case 'z':
        z.add(wire)

  shouldReadGates = False
  for line in f:
    line = line.strip()
    if line == "":
      shouldReadGates = True
      continue
    if shouldReadGates:
      source, target = line.split(" -> ")
      source1, gate, source2 = source.split(" ")
      assert target not in gates
      gates[target] = (gate, source1, source2)
      addValues(target)
    else:
      wire, value = line.split(": ")
      assert wire not in initial
      if wire[0] not in ("x", "y"): # We don't store x and y
        initial[wire] = bool(int(value))
      addValues(wire)

  memoized = {}

  def solve(wire):
    if wire in initial:
      return initial[wire]
    if wire in memoized:
      return memoized[wire]
    assert wire in gates
    gate, source1, source2 = gates[wire]
    match gate:
      case 'AND':
        memoized[wire] = solve(source1) and solve(source2)
      case 'OR':
        memoized[wire] = solve(source1) or solve(source2)
      case 'XOR':
        v1, v2 = solve(source1), solve(source2)
        memoized[wire] = (v1 or v2) and not (v1 and v2)
    return memoized[wire]

  def isSum():
    for i in range(2**len(x)):
      for j in range(2**len(y)):
        memoized = {}
        for k in x:
          memoized[k] = bool((i >> int(k[1:]))&0b1)
        for k in y:
          memoized[k] = bool((j >> int(k[1:]))&0b1)
        result = 0
        for i in sorted(z)[::-1]:
          result <<= 1
          result |= solve(i)
        if result != i+j:
          return False
    return True


  def makeSwitch(switch):
    for i in range(NUMBER_OF_SWITCH):
      gates[switch[i]], gates[switch[i+1]] = gates[switch[i+1]], gates[switch[i]]
  
  print(gates)
  possibleSwitches = itertools.combinations(gates, NUMBER_OF_SWITCH*2)
  for i in possibleSwitches:
    makeSwitch(i)
    if isSum():
      break
    makeSwitch(i)
  else:
    assert False
  print(",".join(sorted(i)))
