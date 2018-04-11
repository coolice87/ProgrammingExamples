package mp

import "fmt"
import "time"

type Mp3Player struct{
	stat int
	progress int
}

func (p *Mp3Player)Play(source string){
	fmt.Println("Playing MP3 music", source)
	p.progress = 0

	for p.progress < 100 {
		time.Sleep(100 * time.Millisecond)
		fmt.Println(".")
		p.progress += 10
	}

	fmt.Println("\n Finished playing", source)
}

