#!/bin/bash

for index in {1..50}
do
	shiftctrl -p 4 -w 0xA # Writes 1010 to the shift register

	sleep 0.1

	shiftctrl -p 4 -w 0x5 # Writes 0101 to the shift register

	sleep 0.1
done

exit 0
