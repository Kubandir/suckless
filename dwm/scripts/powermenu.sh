#!/bin/bash

function powermenu {
	options="  Shutdown\n  Restart\n  Sleep\n  Cancel"
	selected=$(echo -e "$options" | dmenu -c -g 1 -fn "JetBrainsMono Nerd Font" \
		-nb "#1a1b26" -nf "#c0caf5" \
		-sb "#9d7cd8" -sf "#1a1b26" \
		-shb "#bb9af7" -shf "#1a1b26" \
		-nhb "#292e42" -nfh "#c0caf5" \
		-l 5 -h 40 -p '')
	case "$selected" in
		"  Shutdown") systemctl poweroff ;;
		"  Restart") systemctl reboot ;;
		"  Sleep") systemctl suspend ;;
		*) return ;;
	esac
}

powermenu
