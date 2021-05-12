# shiftctrl

shiftctrl is a simple raspberry pi command-line tool that controls shift registers that are connected to the raspberry pi. Shiftctrl uses the [shiftr](https://github.com/TheShoutingParrot/shiftr) library.

# Installation

To install shiftctrl just run `make install` in this directory. This will install the program to PREFIX/bin. Prefix is defined in the [Makefile](Makefile)

# Usage

## Configuring the pins

To control the shift register(s) that the raspberry pi is connected to, the proper pins must be defined. To specify the pins you must use the `-*p` or `-set-*-pin`. If you don't want to always specify them you must change the defaults that are defined in [include/shiftctrl.h](include/shiftctrl.h). 


By default the raspberry pi's pin 11 is (assumed to be) connected to the data pin, pin 15 to the clock pin, pin 23 to the latch pin, pin 21 to the reset pin and pin 19 to the enable pin.


If your data pin would be connected to the the raspberry pi's pin 3, the clock pin to pin 5, the latch pin to pin 7, the reset pin to pin 8 and the enable to the pin 10 the command that you would use would look like this:

```
shiftctrl -dp 3 -cp 5 -lp 7 -rp 8 -ep 10...
```

or like this:

```
shiftctrl -set-data-pin 3 -set-data-pin 5 -set-clock-pin 7 -set-reset-pin 8 -set-enable-pin 10...
```

NOTE: the `...` in the above examples just means that the command would continue from there.

## Writing data to the shift register

Writing data is done by the `-w` or `-write` argument which must be followed by the data that will be written to the shift register.

The `-w VALUE` argument will result also in the output being updated. This can be turned off by  the `-no` argument.

### Specifing the amount of outputs

Specifing the amount of outputs in the shift register that the program will write to can be done by the `-p` or `-pins` argument which must be followed with the amount of outputs/*pins* that the shift register has.

For example, to write 0xBEEF to a shift register (or shift registers that have been linked together) that has/have 16 outputs you must run the following command:

```
shiftctrl -w 0xBEEF -p 16
```

## Enabling and disabling 

To enable the output of the register the `-e` argument must be used when running the program and to disable the `-d` argument.

## Resetting

To reset the shift registers data use the `-r` argument.

# dance.sh - a simple shell script example

The [dance.sh](examples/dance.sh) shell script demonstrates what can be done with this program. This example does exactly the same thing as the shiftr's example program [dance.c](https://github.com/TheShoutingParrot/shiftr/blob/main/examples/dance.c). The script just writes 1010 and 0101 to the shift register 50 times in a row so that it looks like the leds are doing a little "dance".

The script is just runs a simple loop that looks like this:

```sh
for index in {1..50}
do
        shiftctrl -p 4 -w 0xA # Writes 1010 to the shift register

        sleep 0.1

        shiftctrl -p 4 -w 0x5 # Writes 0101 to the shift register

        sleep 0.1
done
```
