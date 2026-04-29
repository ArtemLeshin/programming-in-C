package main

import (
	"fmt"
)

type person struct {
	name string
	age  int
}

var tom struct {
	name string
	age  int
}

type person1 struct {
	string
	int
}

type person3 struct {
	string
	company string
	int
}

func increment_age(user *person) {
	user.age += 1
	fmt.Println(*user) // {Tom 42}
}

func main() {
	// var tom person = person{"Tom", 23}
	// var alice person = person{age: 23, name: "Alice"}
	// bob := person{name: "Bob", age: 31}
	// undefined := person{}
	// fmt.Println(tom)
	// fmt.Println(alice)
	// fmt.Println(bob)
	// fmt.Println(undefined)

	// fmt.Println(tom.name) // Tom
	// fmt.Println(tom.age)  // 23

	// tom.age = 38 // изменяем значение
	// fmt.Println(tom.name, tom.age)

	// tom.name = "Tom"
	// tom.age = 23
	// fmt.Println(tom.name) // Tom
	// fmt.Println(tom.age)  // 23

	// dima := struct { // объявление переменной анонимной структуры
	// 	name string
	// 	age  int
	// }{ // инициализация переменной
	// 	name: "Dima",
	// 	age:  41,
	// }

	// fmt.Println(dima.name) // Tom
	// fmt.Println(dima.age)  // 41

	// nim := person1{"Nim", 41}
	// fmt.Println(nim) // {Tom 41}

	// tom1 := person3{"Tom", "Google", 41}
	// fmt.Println(tom1)

	//указатели

	// tom := person{name: "Tom", age: 22}
	// var p_tom *person = &tom
	// fmt.Println(p_tom.name) // Tom
	// fmt.Println(p_tom.age)  // 22

	// p_tom.age = 23 // меняем значение поля через указатель
	// fmt.Println(tom.age)

	// fmt.Println((*p_tom).name) // Tom
	// fmt.Println((*p_tom).age)  // 22

	// (*p_tom).age = 28
	// fmt.Println(tom.age)

	// var p_age *int = &tom.age // указатель на поле tom.age
	// *p_age = 35               // изменяем значение поля
	// fmt.Println(tom.age)

	//new

	// tom := new(person)

	// fmt.Println(*tom) // { 0}

	// tom.name = "Tom"
	// tom.age = 41
	// fmt.Println(*tom) // {Tom 41}

	// // анонимная структура с new
	// bob := new(struct {
	// 	name, company string
	// 	age           int
	// })

	// fmt.Println(*bob) // {  0}

	// bob.name = "Bob"
	// bob.company = "Google"
	// bob.age = 46

	// fmt.Println(*bob)

	//копирование

	// tom := person{"Tom", 41}

	// tomas := tom // копирование структуры tom
	// tomas.age = 18

	// // изменение одной структуры никак не влияет на другую
	// fmt.Println(tom.age)   // 41
	// fmt.Println(tomas.age) // 18

	// //Передача структур в функции

	// tom := person{"Tom", 41}
	// // в функцию передается адрес структуры tom
	// increment_age(&tom)

	// // изменение структуры внутри функции по указателю приведет к изменению оригинальной структуры
	// fmt.Println(tom) // {Tom 42}

	// //Сравнение структур

	tom := person{"Tom", 41}
	bob := person{"Bob", 41}
	tomas := person{"Tom", 41}

	fmt.Println("tom == bob:", tom == bob)     // tom == bob: false
	fmt.Println("tom == tomas:", tom == tomas) // tom == tomas: true
}
