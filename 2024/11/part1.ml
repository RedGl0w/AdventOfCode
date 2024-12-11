let rec blink (l:int list) (acc: int list) :int list = match l with
  | [] -> List.rev acc
  | h::t ->
    if h = 0 then
      blink t (1::acc)
    else
      let s = string_of_int h in
      let l = String.length s in
      if (l mod 2) = 0 then
          let a = int_of_string (String.sub s 0 (l/2)) in
          let b = int_of_string (String.sub s (l/2) (l/2)) in
          blink t (a::b::acc)
      else
        blink t ((h*2024)::acc)

let nblink (n:int) (l:int list): int list =
  let l' = ref l in
  for i = 0 to (n-1) do
    l' := blink (!l') []
  done;
  !l'

let parse_input (filename: string) :int list =
  let ic = open_in filename in
  try
    let line = input_line ic in
    let result = List.map int_of_string (String.split_on_char ' ' line) in
    close_in ic;
    result
  with e ->
    close_in_noerr ic;
    raise e
    
let result = nblink 25 (parse_input "input.txt")
let _ = Printf.printf "Number of stones : %d\n" (List.length result)
