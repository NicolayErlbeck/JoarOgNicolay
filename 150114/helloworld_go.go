// Go 1.2
// go run helloworld_go.go

package main

import (
    . "fmt" // Using '.' to avoid prefixing functions with their package names
    . "runtime" // This is probably not a good idea for large projects...
    . "time"
)

var i = 0


func adder(chan1 chan int) {
    for x := 0; x < 1000000; x++ {
	<- chan1
        i++
	chan1 <- 1
    }
}

func substraher(chan1 chan int) {
    for x := 0; x < 1000001; x++ {
	<- chan1
        i--
	chan1 <- 1 //kunne også sendt i ut på kanalen!
    }
}

func main() {
    chan1 := make(chan int, 1)
    chan1 <- 1

    GOMAXPROCS(NumCPU()) // I guess this is a hint to what GOMAXPROCS does...
    go adder(chan1) // This spawns adder() as a goroutine
    go substraher(chan1) 
    for x := 0; x < 50; x++ {
        Println(i)
    }
    // No way to wait for the completion of a goroutine (without additional syncronization)
    // We'll come back to using channels in Exercise 2. For now: Sleep
    Sleep(1000*Millisecond)
    Println("Done:", i);
}
