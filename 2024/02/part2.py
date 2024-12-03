def isSafe(report):
  ascending = report[0] <= report[1]
  for i in range(len(report)-1):
    if abs(report[i]-report[i+1]) > 3:
      return False
    if (ascending and report[i] >= report[i+1]) or (not ascending and report[i] <= report[i+1]):
      return False
  return True 

with open("input.txt", "r") as f:
  counter = 0
  for line in f.readlines():
    integers = list(map(int, line.strip().split(" ")))
    # This could be optimized, but we will just bruteforcing deleting an element
    if isSafe(integers):
      counter += 1
      continue
    for i in range(len(integers)):
      e = integers[i]
      del integers[i]
      if isSafe(integers):
        counter += 1
        break
      integers.insert(i, e)
  print(counter)
