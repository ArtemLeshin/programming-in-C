package task03

import "errors"

type User struct {
	ID   int
	Name string
	Age  int
}

func FindUserByID(users []User, id int) (*User, error) {
	var result *User

	for i := range users {
		if users[i].ID == id {
			if result != nil {
				return nil, errors.New("duplicate user id")
			}
			result = &users[i]
		}
	}

	if result == nil {
		return nil, errors.New("user not found")
	}
	
	return result, nil
}
