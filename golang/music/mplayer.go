//music play main process

package main

import(
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"

	"music/lib"
	"music/play"
)

var lib *mlib.MusicManager
var id int =1
var ctrl, signal chan int

func handleLibCommands(tokens []string){
	switch tokens[1]{
		case "list":
			for i:=0; i<lib.Len(); i++ {
				m,_ := lib.Get(i)
				fmt.Println(i+1, ":", m.Id, m.Name, m.Source, m.Type)
			}
		case "add":
			if len(tokens) == 6 {
				lib.Add(&mlib.MusicEntry{strconv.Itoa(id), tokens[2],
				tokens[3], tokens[4], tokens[5]})
				id++
			}else{
				fmt.Println("Usage: lib add <name> <artist><source><type>")
			}
		case "remove":
			if len(tokens) == 3 {
				index, _ := strconv.Atoi(tokens[2])
				fmt.Println("index:", index)
				lib.Remove(index)
			}else{
				fmt.Println("Usage: lib remove<index>")
			}
		default:
			fmt.Println("Unrecognized lib command:", tokens[1])
	}
}


func handlePlayCommand(tokens []string){
	if len(tokens) != 2 {
		fmt.Println("Usage: play <name>")
		return
	}

	m := lib.Find(tokens[1])
	if m == nil{
		fmt.Println("The music", tokens[1], "does not exit")
		return
	}

	mp.Play(m.Source, m.Type)
}


func main(){
	fmt.Println(`
				Enter following commands to control the player:
				lib list -- view the exiting music lib
				lib add <name><artist><source><type> -- add a music
				lib remove<name> -- remove the specified musci from the lib
				play <name> -- play the specified music
				`)

	lib = mlib.NewMusicManager()

	r := bufio.NewReader(os.Stdin)

	for{
		fmt.Println("Enter command-> ")
		rawLine, _, _ := r.ReadLine()

		line := string(rawLine)
		if line == "q" || line == "e" {
			break
		}

		tokens := strings.Split(line, " ")
		if tokens[0] == "lib" {
			handleLibCommands(tokens)
		}else if tokens[0] == "play" {
			handlePlayCommand(tokens)
		}else{
			fmt.Println("Unrecongnized command:", tokens[0])	
		}
	}
}

