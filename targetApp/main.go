package main

import (
	"fmt"
	"net/http"
	"time"
)

func main (){
	http.HandleFunc("/", HelloServer)


	http.ListenAndServe(":8080", nil)

}

func HelloServer( w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Hello, %d!", time.Now().Second())
}



