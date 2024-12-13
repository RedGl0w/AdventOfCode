async function loadFile(filename) {
  const lines = (await Deno.readTextFile(filename)).split("\n");
  const map = [];
  for (let i = 0; i < lines.length; i++) {
    for (let j = 0; j < lines[i].length; j++) {
      map.push(lines[i][j]);
    }
  }
  return [map, lines[0].length];
}

// This implementation is maybe a bit overengineered, but at least it works :p
// (and it might be usefull fort part2)
class uf {
  constructor(size) {
    this.parents = Array(size);
    this.ranks = Array(size).fill(0);
    for (let i = 0; i < size; i++) {
      this.parents[i] = i;
    }
  }

  find(a) {
    if (this.parents[a] != a) {
      this.parents[a] = this.find(this.parents[a]);
    }
    return this.parents[a];
  }

  union(a, b) {
    const aRoot = this.find(a);
    const bRoot = this.find(b);
    if (aRoot != bRoot) {
      if (this.ranks[aRoot] < this.ranks[bRoot]) {
        this.parents[aRoot] = bRoot;
      } else {
        this.parents[bRoot] = aRoot;
        if (this.ranks[aRoot] == this.ranks[bRoot]) {
          this.ranks[aRoot]++;
        }
      }
    }
  }
}

function callOnNeighbours(size, i, j, callBack) {
  if (i > 0) {
    callBack(i - 1, j);
  }
  if (i < size - 1) {
    callBack(i + 1, j);
  }
  if (j > 0) {
    callBack(i, j - 1);
  }
  if (j < size - 1) {
    callBack(i, j + 1);
  }
}

function generateRegion(plots, size) {
  let result = new uf(plots.length);
  for (let i = 0; i < size; i++) {
    for (let j = 0; j < size; j++) {
      const index1 = i * size + j;
      const plant = plots[index1];
      callOnNeighbours(size, i, j, (x, y) => {
        const index2 = x * size + y;
        if (plant == plots[index2]) {
          result.union(index1, index2); 
        }
      })
    }
  }
  return result;
}

function computeAreasAndPerimeters(regions, size) {
  // Tree in uf are compressed (no more union)
  // We can simply multiplicate element by element in arrays to get score confidently
  const areas = new Array(size * size).fill(0);
  const perimeters = new Array(size * size).fill(0);
  for (let i = 0; i < size; i++) {
    for (let j = 0; j < size; j++) {
      const index1 = i * size + j;
      const parent = regions.find(index1);
      areas[parent]++;
      // If we are on a border, we don't have neighbours, increase perimeter
      perimeters[parent] += (i === 0) + (i === size - 1) + (j === 0) + (j === size - 1);
      callOnNeighbours(size, i, j, (x, y) => {
        const index2 = x * size + y;
        if (parent != regions.find(index2)) {
          perimeters[parent]++;
        }
      });
    }
  }
  const prices = new Array(size * size);
  for (let i = 0; i < size * size; i++) {
    prices[i] = areas[i]*perimeters[i]
  }
  const totalPrice = prices.reduce((acc, v) => acc + v, 0);
  return totalPrice;
}

function print(l, size) {
  for (let i = 0; i < size; i++) {
    console.log(l.slice(size * i, size * (i + 1)).join(" "));
  }
  console.log("------------------")
}

loadFile("input.txt").then(input => {
  const [plots, size] = input;
  const regions = generateRegion(plots, size);
  const totalPrice = computeAreasAndPerimeters(regions, size);
  console.log(totalPrice)
})
