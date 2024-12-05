function verifyLine(l, order)
  for i in 1:length(l)-1
    for j in i+1:length(l)
      if !(l[i] in keys(order))
        return false
      end
      if !(l[j] in keys(order[l[i]]))
        return false
      end
    end
  end
  return true
end

function orderLine(l, order)
  if length(l) == 1
    return l
  end
  for i in 1:length(l)
    if l[i] in keys(order)
      wrongStart = false
      for j in 1:length(l)
        if i != j
          if !(l[j] in keys(order[l[i]]))
            wrongStart = true
            break
          end
        end
      end
      if !wrongStart
        firstElement = l[i]
        toSort = deleteat!(l, i)
        ordered = orderLine(toSort, order)
        pushfirst!(ordered, firstElement)
        return ordered
      end
    end
  end
  return []
end

open("input.txt", "r") do f
  hasPassedBlankLine = false
  order = Dict()
  total = 0
  for line in readlines(f)
    if line == ""
      hasPassedBlankLine = true
      continue
    end
    if !hasPassedBlankLine
      # We start by processing order constrains
      x,y = map((s) -> parse(Int, s), split(line, "|"))
      if !(x in keys(order))
        order[x] = Dict()
      end
      order[x][y] = true
    else
      update = map((s) -> parse(Int, s), split(line, ","))
      if !verifyLine(update, order)
        ordered = orderLine(update, order)
        middle = ordered[(length(ordered)+1)÷2]
        total += middle
      end
    end
  end
  println("$total")
end