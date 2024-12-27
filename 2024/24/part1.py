with open("input.txt", "r", encoding="utf-8") as f:
  
  memoized = {}
  gates = {}

  output = set()

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
      if target[0] == 'z':
        output.add(target)
    else:
      wire, value = line.split(": ")
      assert wire not in memoized
      memoized[wire] = bool(int(value))
      if wire[0] == 'z':
        output.add(wire)

  def solve(wire):
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

  result = 0
  for i in sorted(output)[::-1]:
    result <<= 1
    result |= solve(i)
  print(result)
