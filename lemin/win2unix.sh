#!/bin/sh
CR=$(printf '\r')
sed -i '' "s/$CR\$//" "$1"
