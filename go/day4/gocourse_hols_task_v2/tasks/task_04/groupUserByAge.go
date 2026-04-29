package task04

import "errors"

type User struct {
	Name string
	Age  int
}

func GroupUsersByAge(users []User) (map[int][]User, error) {
	seen := make(map[string]bool)
	result := make(map[int][]User)
	for i := range users {
		if users[i].Name == "" {
			return nil, errors.New("empty name")
		}
		if users[i].Age < 0 {
			return nil, errors.New("invalid age")
		}
		if seen[users[i].Name] {
			return nil, errors.New("duplicate name")
		}
		seen[users[i].Name] = true
		age := users[i].Age
		result[age] = append(result[age], users[i])
	}

	return result, nil
}
