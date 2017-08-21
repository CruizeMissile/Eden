#!/bin/sh
# vim: set ft=sh:

set -e

if tmux has-session -t eden 2> /dev/null; then
	tmux attach -t eden
	exit
fi

tmux new-session -d -s eden -n vim

tmux send-keys -t eden:vim "vim ." Enter
tmux split-window -t eden:vim -h -p 40
tmux send-keys -t eden:vim.right "git status" Enter
tmux split-window -t eden:vim.right -v -p 30

tmux attach -t eden:vim.left
