interface machine {
  ax: number;
  ay: number;
  bx: number;
  by: number;
  px: number;
  py: number;
}

async function loadFile(filename: string): Promise<Array<machine>> {
  const lines = (await Deno.readTextFile(filename)).split("\n").slice(0, -1);
  const machines: Array<machine> = [];
  for (let i = 0; i < lines.length / 4; i++) {
    let line: string[] = lines[i * 4].split("+");
    const ax = parseInt(line[1].split(",")[0]);
    const ay = parseInt(line[2]);
    line = lines[i * 4 + 1].split("+");
    const bx = parseInt(line[1].split(",")[0]);
    const by = parseInt(line[2]);
    line = lines[i * 4 + 2].split("=");
    // const px = parseInt(line[1].split(",")[0]);
    // const py = parseInt(line[2]);
    const px = parseInt(line[1].split(",")[0])+10000000000000;
    const py = parseInt(line[2])+10000000000000;
    machines.push({ ax, ay, bx, by, px, py });
  }
  return machines;
}

function solve(a: number, b: number, c: number, d: number, u: number, v: number): { x: number, y: number } | null {
  // This function is meant to solve this system :
  // a*x+b*y=u
  // c*x+d*y=v
  // This system corresponds to :
  // ┌     ┐ ┌   ┐    ┌   ┐
  //   a b     x   _    u
  //   c d     y   ¯    v
  // └     ┘ └   ┘    └   ┘
  // The solution is
  // ┌   ┐    ┌     ┐ -1  ┌   ┐       1    ┌       ┐ ┌   ┐
  //   x   _    a b         u    _  _____     d -b     u
  //   y   ¯    c d         v    ¯   det     -c  a     v
  // └   ┘    └     ┘     └   ┘            └       ┘ └   ┘
  const det = a * d - b * c;
  if (det === 0) {
    return null;
  }
  const x = (d * u - b * v) / det;
  const y = (a * v - c * u) / det;
  return { x, y };
}

// console.log(solve(17,84,86,37,7870,6450))
loadFile("input.txt").then((machines: Array<machine>) => {
  let total: number = 0;
  for (const m of machines) {
    const {x, y} = solve(m.ax, m.bx, m.ay, m.by, m.px, m.py);
    if (Number.isInteger(x) && Number.isInteger(y)) {
      total += x * 3 + y;
    }
  };
  console.log(total);
});
