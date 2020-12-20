compile:
	gcc -w main.c -o main
	chmod +x script.sh

clean:
	rm -f main test_file.txt