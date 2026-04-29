package main

import (
	"fmt"
	"reflect"
)

func main() {
	// people := map[string]int{
	// 	"Tom":   1,
	// 	"Bob":   2,
	// 	"Sam":   4,
	// 	"Alice": 8,
	// }
	// fmt.Println(people)          // map[]
	// fmt.Println(people["Alice"]) // 8
	// fmt.Println(people["Bob"])   // 2
	// people["Bob"] = 32
	// fmt.Println(people["Bob"])
	// if val, ok := people["Tom"]; ok {
	// 	fmt.Println(val)
	// }
	// for key, value := range people {
	// 	fmt.Println(key, value)
	// }

	//make

	// people := make(map[string]int)
	// people := map[string]int{"Tom": 1, "Bob": 2}
	// people["Kate"] = 128
	// fmt.Println(people)

	//сравнение reflect

	people1 := map[string]int{"Tom": 1, "Bob": 2, "Sam": 3}
	people2 := map[string]int{"Tom": 1, "Bob": 2, "Sam": 3}
	people3 := map[string]int{"Tom": 1, "Bob": 2, "Sam": 4}
	fmt.Println("people1 == people2:", reflect.DeepEqual(people1, people2)) // people1 == people2: true
	fmt.Println("people1 == people3:", reflect.DeepEqual(people1, people3))
}
