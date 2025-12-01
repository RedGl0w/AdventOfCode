#{
  let input = read("input.txt").split("\n").filter(it => it.len() != 0)

  input = input.map(it => (it.at(0), int(it.slice(1))))

  let pos = 50
  let size = 100
  let count = 0

  for (dir, len) in input {
    if (dir == "L") {
      count += calc.quo(calc.abs(pos - len), size) + int((pos != 0) and (pos <= len))
      pos = calc.rem(pos - len, size)
      if (pos < 0) {
        pos += size
      }
    } else {
      assert(dir == "R")
      count += calc.quo(pos + len, size)
      pos = calc.abs(calc.rem(pos + len, size))
    }
  }

  [
    Number of times dial was at 0 : #count
  ]
}
