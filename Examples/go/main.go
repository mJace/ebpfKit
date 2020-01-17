package main

import (
	"container/list"
	"fmt"
	"math/rand"
	"net/http"
	"runtime"
	"strconv"
	"time"
	"log"
	"sync"
)

type Duration int64


var prodLock *sync.Mutex
var conLock *sync.Mutex

const maxLength  = 10

func producer(l *list.List, delay int64) {
	for {
		prodLock.Lock()
		if l.Len() < maxLength {
			tmp := rand.Intn(100)
			l.PushFront(tmp)
			time.Sleep(time.Duration(delay) * time.Second)

		}
		prodLock.Unlock()
	}
}

func consumer(l *list.List, delay int64) {
	for {
			conLock.Lock()
			time.Sleep(time.Duration(delay) * time.Second)
			if l.Len() != 0 {
				tmp := l.Back()
				_ = l.Remove(tmp)
			}
			conLock.Unlock()

	}
}

func dumpList() string{
	var retStr string
	if dataList.Len() == 0 {
		return ""
	}

	for e := dataList.Front(); e != nil; e = e.Next() {
		retStr = retStr+ strconv.Itoa(e.Value.(int))+"\n"
	}
	return retStr
}

var dataList *list.List

func main (){

	prodLock = new(sync.Mutex)
	conLock = new(sync.Mutex)
	http.HandleFunc("/", HelloServer)

	dataList = list.New()

	n := runtime.NumCPU()
	if n < 2 {
		log.Fatal("Need at least 2 cores")
	}

	runtime.GOMAXPROCS(runtime.NumCPU())

	go producer(dataList, 1)
	go producer(dataList, 1)
	go producer(dataList, 2)
	go producer(dataList, 3)

	go consumer(dataList, 1)
	go consumer(dataList, 5)
	go consumer(dataList, 3)
	go consumer(dataList, 4)



	http.ListenAndServe(":8080", nil)


}

func HelloServer( w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Data Size, %d! \n%s", dataList.Len(), dumpList())

}



