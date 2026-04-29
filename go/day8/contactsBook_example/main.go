package main

import (
	auth "contactsBook/authentication"
	"contactsBook/controllers"
	"fmt"
	"net/http"
	"os"

	"github.com/gorilla/mux"
)

func main() {
	router := mux.NewRouter()
	router.Use(auth.JwtAuthentication)

	router.HandleFunc("/user/new", controllers.CreateAccount).Methods("POST")
	router.HandleFunc("/user/login", controllers.LoginAccount).Methods("POST")
	router.HandleFunc("/contacts/new", controllers.CreateContact).Methods("POST")
	router.HandleFunc("/me/contacts", controllers.GetContacts).Methods("GET")
	router.HandleFunc("/contact/{id:[0-9]+}", controllers.UpdateContact).Methods("PUT")
	router.HandleFunc("/contact/{id:[0-9]+}", controllers.DeleteContact).Methods("DELETE")

	port := os.Getenv("PORT")
	if port == "" {
		port = "8000"
	}

	err := http.ListenAndServe(":"+port, router)
	if err != nil {
		fmt.Print(err)
	}
}
