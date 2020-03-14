package main

import (
	"os"
	"fmt"
	"log"
    "net/http"
)

var whoToGreet string = "World"
var fromWho string = "from Go"

func main() {
	envWho := os.Getenv("WHO")
	if envWho != "" {
		whoToGreet = envWho
	}
	hostname, _ := os.Hostname()

	if hostname != "" {
		fromWho += " @" + hostname
	}

	http.HandleFunc("/", HelloServer)
	
	log.Printf("Listening on port 8080")
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		log.Fatal(err)
	}
}

func HelloServer(w http.ResponseWriter, r *http.Request) {
	log.Printf("%s %s %s\n", r.RemoteAddr, r.Method, r.URL)
	fmt.Fprintf(w, "Hello, %s! %s", whoToGreet, fromWho)
}