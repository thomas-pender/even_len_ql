package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"sort"
	"strconv"
	"strings"
)

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

type corrs [][]int

func (c corrs) Len() int { return len(c) }
func (c corrs) Less(i, j int) bool {
	for k := 0; k < len(c[i]); k++ {
		if c[i][k] == c[j][k] {
			continue
		}
		return c[i][k] < c[j][k]
	}
	return false
}
func (c corrs) Swap(i, j int) { c[i], c[j] = c[j], c[i] }

func fileToMap(file string) map[string][]string {
	f, err := os.Open(file)
	if err != nil {
		log.Fatalf("fileToMap -- failed to open file %s", file)
	}

	keys := make(map[string][]string)

	input := bufio.NewScanner(f)
	for input.Scan() {
		x := strings.Split(input.Text(), " ")
		if len(x) < 2 {
			log.Fatalf("len(x) less than 2")
		}
		keys[x[1]] = append(keys[x[1]], x[0])
	}

	f.Close()

	return keys
}

func mapToCorrs(corr map[string][]string) corrs {
	keys := make(corrs, 0, len(corr))

	for a, _ := range corr {
		b := strings.Split(a, ",")
		c := make([]int, 0, len(b))
		for _, bb := range b {
			cc, _ := strconv.Atoi(bb)
			c = append(c, cc)
		}
		keys = append(keys, c)
	}
	sort.Sort(keys)

	return keys
}

func legendre_check(Akeys corrs, Bkeys corrs, A map[string][]string, B map[string][]string) {
	for i, j := 0, len(Bkeys)-1; i < len(Akeys) && j >= 0; {
		flag := true
		for k := 0; k < len(Akeys[i]); k++ {
			val := Akeys[i][k] + Bkeys[j][k]
			switch {
			case val < -2:
				flag = false
				i++
			case val > -2:
				flag = false
				j--
			}
			if !flag {
				break
			}
		}

		if flag {
			x := strings.Trim(strings.Join(strings.Fields(fmt.Sprint(Akeys[i])), ","), "[]")
			y := strings.Trim(strings.Join(strings.Fields(fmt.Sprint(Bkeys[j])), ","), "[]")

			for _, a := range A[x] {
				for _, b := range B[y] {
					fmt.Printf("%s\t[", a)
					for _, z := range strings.Split(x, ",") {
						fmt.Printf("%3s", z)
					}
					fmt.Printf(" ]\n%s\t[", b)
					for _, z := range strings.Split(y, ",") {
						fmt.Printf("%3s", z)
					}
					fmt.Printf(" ]\n\n")
				}
			}

			i++
			j--
		}
	}
}

func main() {
	if len(os.Args[1:]) != 2 {
		log.Fatalf("routine requires 2 arguments: A.txt B.txt")
	}

	/* read in files */
	A := fileToMap(os.Args[1])
	B := fileToMap(os.Args[2])

	/* sort keys */
	Akeys := mapToCorrs(A)
	Bkeys := mapToCorrs(B)

	/* check for Legendre pairs */
	legendre_check(Akeys, Bkeys, A, B)
}
