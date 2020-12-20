command="./main test2.txt < input.txt; exec zsh"
gnome-terminal -- /bin/sh -c "$command" & gnome-terminal -- /bin/sh -c "$command"