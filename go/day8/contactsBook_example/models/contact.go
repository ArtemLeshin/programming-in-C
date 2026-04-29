package models

import (
	"contactsBook/utils"
	"fmt"

	"github.com/jinzhu/gorm"
)

type Contact struct {
	gorm.Model
	Name   string `json:"name"`
	Phone  string `json:"phone"`
	UserId uint   `json:"user_id"`
}

func (contact *Contact) ValidateContact() (map[string]interface{}, bool) {
	if contact.Name == "" {
		return utils.Message(false, "Name cannot be empty!"), false
	}

	if contact.Phone == "" {
		return utils.Message(false, "Phone number cannot be empty!"), false
	}

	if contact.UserId <= 0 {
		return utils.Message(false, "User not found!"), false
	}

	return utils.Message(true, "success"), true
}

func (contact *Contact) CreateContact() map[string]interface{} {
	if response, ok := contact.ValidateContact(); !ok {
		return response
	}

	GetDB().Create(contact)

	resp := utils.Message(true, "success")
	resp["contact"] = contact
	return resp
}

func GetContact(id uint) *Contact {
	contact := &Contact{}
	err := GetDB().Table("contacts").Where("id = ?", id).First(contact).Error
	if err != nil {
		return nil
	}
	return contact
}

func GetContacts(user uint) []*Contact {
	contactsSlice := make([]*Contact, 0)
	err := GetDB().Table("contacts").Where("user_id = ?", user).Find(&contactsSlice).Error
	if err != nil {
		fmt.Println(err)
		return nil
	}

	return contactsSlice
}
func (contact *Contact) Update(id uint) map[string]interface{} {
	if response, ok := contact.ValidateContact(); !ok {
		return response
	}

	err := GetDB().Model(&Contact{}).Where("id = ?", id).Updates(contact).Error
	if err != nil {
		return utils.Message(false, "Connection error. Please retry")
	}

	resp := utils.Message(true, "success")
	resp["contact"] = contact
	return resp
}

func DeleteContact(id uint) map[string]interface{} {
	db := GetDB().Where("id = ?", id).Delete(&Contact{})

	if db.Error != nil {
		return utils.Message(false, "Connection error. Please retry")
	}

	if db.RowsAffected == 0 {
		return utils.Message(false, "Contact not found")
	}

	return utils.Message(true, "success")
}
