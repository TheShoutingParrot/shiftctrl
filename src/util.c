#include "shiftctrl.h"

uint8_t convertNumToPin(int n) {
	switch(n) {
		case 3:
			return RPI_GPIO_P1_03;
		case 5:
			return RPI_GPIO_P1_03;
		case 7:
			return RPI_GPIO_P1_07;
		case 8:
			return RPI_GPIO_P1_08;
		case 10:
			return RPI_GPIO_P1_10;
		case 11:
			return RPI_GPIO_P1_11;
		case 12:
			return RPI_GPIO_P1_12;
		case 13:
			return RPI_GPIO_P1_13;
		case 15:
			return RPI_GPIO_P1_15;
		case 16:
			return RPI_GPIO_P1_16;
		case 18:
			return RPI_GPIO_P1_18;
		case 19:
			return RPI_GPIO_P1_19;
		case 21:
			return RPI_GPIO_P1_21;
		case 22:
			return RPI_GPIO_P1_22;
		case 23:
			return RPI_GPIO_P1_23;
		case 24:
			return RPI_GPIO_P1_24;
		case 26:
			return RPI_GPIO_P1_26;

		default:
			die("pin number (%d) is invalid!", n);
	}
}

void usage(void) {
	printf("usage: shiftctrl [-w/-write DATA] [-p/-pins outputs] [-*p/-set-*-pin pin] [-e/-enable] [-d/-disable]\n"
		"\t\t [-r/-reset] [-no/-no-output] [-h/-help]\n"
		"For more help run shiftctrl using the -h argument\n");
	
	exit(EXIT_SUCCESS);
}

void help(void) {
	puts("shiftctrl - a program to control shift registers from the command-line");
	printf("usage: shiftctrl [-w/-write DATA] [-p/-pins outputs] [-*p/-set-*-pin pin] [-e/-enable] [-d/-disable]\n"
		"\t\t [-r/-reset] [-no/-no-output] [-h/-help]\n\n");

	printf("command-line arguments:\n"
		"-w/-write DATA\t\tWrites DATA to the shift register\n"
		"-p/-pins OUTPUTS\tSpecifies the amount of outputs that the shift register has. \n"
		"By default this is set to 8\n"
		"-e/-enable\t\tEnables the shift register's output (sets the enable pin to ground)\n"
		"-r/-reset\t\tResets the shift register's data (using the reset pin)\n"
		"-no/-no-output\t\tWhen this is enabled the program doesn't update the output when writing\n"
		"-h/-help\t\tThe program prints this help message\n"
		"-*p/set-*-pin PIN\tSpecifies an inputs pin on the raspberry pi.\n" 
		"The different variations of this command are:\n"
		"\t-dp/-set-data-pin\tSpecifies the shift registers data input's pin\n"
		"\t-cp/-set-clock-pin\tSpecifies the shift registers clock input's pin\n"
		"\t-lp/-set-latch-pin\tSpecifies the shift registers latch input's pin\n"
		"\t-rp/-set-reset-pin\tSpecifies the shift registers reset input's pin\n"
		"\t-ep/-set-enable-pin\tSpecifies the shift registers enable input's pin\n"
		"\n"
		"If you find a bug or any other type of issue please report it on github (link: https://github.com/TheShoutingParrot/shiftrctrl)"
		"\n");


	exit(EXIT_SUCCESS);
}

void die(const char *fmt, ...) {
	va_list vargs;

	va_start(vargs, fmt);
	vfprintf(stderr, fmt, vargs);

	va_end(vargs);

	if(*(fmt+strlen(fmt)-1) == ':') {
		fputc(' ', stderr);
		perror(NULL);
	}

	else
		fputc('\n', stderr);

	exit(1);
}
