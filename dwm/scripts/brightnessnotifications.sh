#!/bin/bash

function get_brightness() {
    brightnessctl get
}

function get_max_brightness() {
    brightnessctl m
}

function get_percentage() {
    current=$(get_brightness)
    max=$(get_max_brightness)
    echo $(( current * 100 / max ))
}

function set_brightness() {
    percent=$1
    max=100
    if (( percent < 1 )); then
        percent=1
    elif (( percent > max )); then
        percent=$max
    fi
    brightnessctl set "${percent}%"
}

function send_notification() {
    percent=$(get_percentage)
    dunstify -a "brightnessnotification" -u normal -r "9994" -h int:value:"$percent" "Brightness: ${percent}" -t 2000
}

current=$(get_percentage)

case $1 in
up)
    if (( current >= 100 )); then
        new=100
    elif (( current >= 5 )); then
        new=$(( current + 5 ))
        (( new > 100 )) && new=100
    else
        new=$(( current + 1 ))
        (( new > 100 )) && new=100
    fi
    set_brightness $new
    send_notification
    ;;
down)
    if (( current > 5 )); then
        new=$(( current - 5 ))
        (( new < 1 )) && new=1
    else
        new=$(( current - 1 ))
        (( new < 1 )) && new=1
    fi
    set_brightness $new
    send_notification
    ;;
esac
