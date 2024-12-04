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
  // (We could also improve limits of the loop without searching on the border)
  for row in range(height) {
    for column in range(width) {

      // We only start searching when we are on a A
      if getChar(row,column) == "A" {
        let numberOfMatch = 0;
        // And we check each diagonal (this could be easily improved, but I don't have time to)
        if getChar(row - 1, column - 1) == "M" {
          if getChar(row + 1, column + 1) == "S" {
            numberOfMatch += 1;
          }
        }
        if getChar(row - 1, column - 1) == "S" {
          if getChar(row + 1, column + 1) == "M" {
            numberOfMatch += 1;
          }
        }
        if getChar(row - 1, column + 1) == "M" {
          if getChar(row + 1, column - 1) == "S" {
            numberOfMatch += 1;
          }
        }
        if getChar(row - 1, column + 1) == "S" {
          if getChar(row + 1, column - 1) == "M" {
            numberOfMatch += 1;
          }
        }
        if numberOfMatch == 2 {
          total += 1
        }
      }
    }
  }
  [
    *Total number of X-MAS : #total*
  ]
}
