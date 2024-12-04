#{
  let input = read("input.txt").split("\n").filter(it => it.len() != 0);

  let height = input.len();
  let width = input.at(0).len();

  // Ensure we have a square
  for i in range(height) {
    assert(input.at(i).len() == width);
  }

  // Helper function to avoid getting out of bounds values
  let getChar(i, j) = {
    if i >= height or i < 0 {
      return none
    }
    if j >= width or j < 0 {
      return none
    }
    return input.at(i).at(j)
  }

  let total = 0;

  // We check at each possible position of the grid the word starting at this position
  for row in range(height) {
    for column in range(width) {
      let key = "XMAS";

      // Iter on all possible direction (upwards, downwards, left, right and the 4 diagonals)
      for rowDirection in (-1,0,1) {
        // We ensure ourselves that we are moving
        let possibleColumnDirection = (-1, 1);
        if rowDirection != 0 {
          possibleColumnDirection.push(0);
        }
        for columnDirection in possibleColumnDirection {
          // We check each char
          let i = row;
          let j = column;
          let matched = true;
          for letter in key {
            if letter == getChar(i,j) {
              i += rowDirection;
              j += columnDirection;
            } else {
              matched = false;
              break
            }
          }
          if matched {
            total += 1;
          }
        }
      }
    }
  }
  [
    *Total number of XMAS : #total*
  ]
}
