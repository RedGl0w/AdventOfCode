package main

import (
	"fmt"
	"os"
)

// Double automata like
// We keep track on our position on the mul(n1,n2) for the first part
// And also of the do() don't() with a second automata, while reading input with both

const (
	readM     = 0
	readU     = 1
	readL     = 2
	readLP    = 3
	readN1    = 4
	readComma = 5
	readN2    = 6
	readRP    = 7

	doReadD   = 8
	doReadO   = 9
	doReadN   = 10
	doReadApo = 11
	doReadT   = 12
	doReadLP  = 13
	doReadRP  = 14
)

func parseInt(s string, initialPosition int) (parsed bool, value int, finalPosition int) {
	intValue := 0
	for i := initialPosition; i < len(s); i++ {
		if '0' <= s[i] && s[i] <= '9' {
			intValue = intValue*10 + (int(s[i]) - '0')
		} else {
			if i != initialPosition {
				return true, intValue, i - 1
			} else {
				return false, 0, i - 1
			}
		}
	}
	return false, 0, len(s)
}

func main() {
	dat, err := os.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}
	input := string(dat)

	status := readM
	doStatus := doReadD
	enabled := true

	n1 := 0
	n2 := 0
	sumWithoutDo := 0
	sumWithDo := 0
	for i := 0; i < len(input); i++ {
		char := input[i]

		switch doStatus {
		case doReadD:
			if char == 'd' {
				doStatus += 1
			}
		case doReadO:
			if char == 'o' {
				if enabled {
					doStatus = doReadN
				} else {
					doStatus = doReadLP
				}
			} else {
				doStatus = doReadD
			}
		case doReadN:
			if char == 'n' {
				doStatus = doReadApo
			} else {
				doStatus = doReadD
			}
		case doReadApo:
			if char == '\'' {
				doStatus = doReadT
			} else {
				doStatus = doReadD
			}
		case doReadT:
			if char == 't' {
				doStatus = doReadLP
			} else {
				doStatus = doReadD
			}
		case doReadLP:
			if char == '(' {
				doStatus = doReadRP
			} else {
				doStatus = doReadD
			}
		case doReadRP:
			if char == ')' {
				enabled = !enabled
			}
			doStatus = doReadD
		}

		switch status {
		case readM:
			if char == 'm' {
				status += 1
			}
		case readU:
			if char == 'u' {
				status += 1
			} else {
				status = readM
			}
		case readL:
			if char == 'l' {
				status += 1
			} else {
				status = readM
			}
		case readLP:
			if char == '(' {
				status += 1
			} else {
				status = readM
			}
		case readN1:
			parsed, value, finalChar := parseInt(input, i)
			if parsed {
				n1 = value
				i = finalChar
				status += 1
			} else {
				status = readM
			}
		case readComma:
			if char == ',' {
				status += 1
			} else {
				status = readM
			}
		case readN2:
			parsed, value, finalChar := parseInt(input, i)
			if parsed {
				n2 = value
				i = finalChar
				status += 1
			} else {
				status = readM
			}
		case readRP:
			if char == ')' {
				//fmt.Printf("mul(%d,%d)\n", n1, n2)
				sumWithoutDo += n1 * n2
				if enabled {
					sumWithDo += n1 * n2
				}
				status = readM
			} else {
				status = readM
			}
		}
		//fmt.Printf("%c %d\n", char, i)
	}
	fmt.Printf("Sum without do = %d\n", sumWithoutDo)
	fmt.Printf("Sum with do = %d\n", sumWithDo)
}
