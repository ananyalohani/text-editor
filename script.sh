# Note: this only works with zsh on Ubuntu
command="./main test_file.txt < input.txt; exec zsh"
gnome-terminal -- /bin/sh -c "$command" & gnome-terminal -- /bin/sh -c "$command"