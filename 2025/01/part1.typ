#{
  let input = read("input.txt").split("\n").filter(it => it.len() != 0)

  input = input.map(it => (it.at(0), int(it.slice(1))))

  let pos = 50
  let size = 100
  let count = 0

  for (dir, len) in input {
    if (dir == "L") {
      pos -= len
    } else if (dir == "R") {
      pos += len
    } else {
      assert(false)
    }
    pos = calc.rem(pos+size, size)
    if (pos == 0) {
      count += 1
    }
  }

  [
    Number of times dial was at 0 : #count
  ]
}
