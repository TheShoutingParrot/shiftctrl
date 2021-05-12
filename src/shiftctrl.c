#include "shiftctrl.h"

int main(int argc, char *argv[]) {
	struct shiftRegister sr;
	uint8_t arg, amountOfPins, pins[TOTAL_PINS];
	char *endptr; /* this isn't important and is only used by strtol */
	uint64_t writeValue;
	bool valueGiven, enableOutput, disableOutput, 
	     reset, noOutput;

	if(argc < 2)
		usage();

	amountOfPins = DEF_NUM_PINS;
	valueGiven = false;
	enableOutput = false;
	disableOutput = false;
	reset = false;
	noOutput = false;

	pins[DATA_PIN] = DEF_DATA_PIN;
	pins[CLOCK_PIN] = DEF_CLOCK_PIN;
	pins[LATCH_PIN] = DEF_LATCH_PIN;
	pins[RESET_PIN] = DEF_RESET_PIN;
	pins[ENABLE_PIN] = DEF_ENABLE_PIN;

	for(arg = 1; arg < argc; arg++) {
		if(!strcmp(argv[arg], "-w") || !strcmp(argv[arg], "-write")) {
			if(argc <= arg+1)
				usage();

			writeValue = strtol(argv[++arg], &endptr, 0);

			valueGiven = true;
		}

		else if(!strcmp(argv[arg], "-p") || !strcmp(argv[arg], "-pins")) {
			if(argc <= arg+1)
				usage();

			amountOfPins = strtol(argv[++arg], &endptr, 0);
		} 

		else if(!strcmp(argv[arg], "-dp") || !strcmp(argv[arg], "-set-data-pin")) {
			if(argc <= arg+1)
				usage();

			pins[DATA_PIN] = convertNumToPin(strtol(argv[++arg], &endptr, 0));
		}

		else if(!strcmp(argv[arg], "-cp") || !strcmp(argv[arg], "-set-clock-pin")) {
			if(argc <= arg+1)
				usage();

			pins[CLOCK_PIN] = convertNumToPin(strtol(argv[++arg], &endptr, 0));
		}

		else if(!strcmp(argv[arg], "-lp") || !strcmp(argv[arg], "-set-latch-pin")) {
			if(argc <= arg+1)
				usage();

			pins[LATCH_PIN] = convertNumToPin(strtol(argv[++arg], &endptr, 0));
		}

		else if(!strcmp(argv[arg], "-rp") || !strcmp(argv[arg], "-set-reset-pin")) {
			if(argc <= arg+1)
				usage();

			pins[RESET_PIN] = convertNumToPin(strtol(argv[++arg], &endptr, 0));
		}

		else if(!strcmp(argv[arg], "-ep") || !strcmp(argv[arg], "-set-enable-pin")) {
			if(argc <= arg+1)
				usage();

			pins[ENABLE_PIN] = convertNumToPin(strtol(argv[++arg], &endptr, 0));
		}

		else if(!strcmp(argv[arg], "-e") || !strcmp(argv[arg], "-enable")) {
			enableOutput = true;
		}


		else if(!strcmp(argv[arg], "-d") || !strcmp(argv[arg], "-disable")) {
			disableOutput = true;
		}

		else if(!strcmp(argv[arg], "-r") || !strcmp(argv[arg], "-reset")) {
			reset = true;
		}

		else if(!strcmp(argv[arg], "-no") || !strcmp(argv[arg], "-no-output")) {
			noOutput = true;
		}
		
		else if(!strcmp(argv[arg], "-h") || !strcmp(argv[arg], "-help")) {
			help();
		}

		else {
			usage();
		}
	}
	
	srInitGpioControl(); /* inits gpio control with either the bcm2835 library or the wiringPi library*/

	if(enableOutput && !disableOutput)
		sr = initShiftRegister(amountOfPins, pins[DATA_PIN], pins[CLOCK_PIN], pins[LATCH_PIN],
				pins[RESET_PIN], pins[ENABLE_PIN], true);

	else if(disableOutput && !enableOutput)
		sr = initShiftRegister(amountOfPins, pins[DATA_PIN], pins[CLOCK_PIN], pins[LATCH_PIN],
				pins[RESET_PIN], pins[ENABLE_PIN], false);

	else
		sr = initShiftRegister(amountOfPins, pins[DATA_PIN], pins[CLOCK_PIN], pins[LATCH_PIN],
				pins[RESET_PIN], pins[ENABLE_PIN], true);

	if(reset) {
		srReset(sr);

		if(!noOutput)
			srUpdateOutput(sr);
	}
	else if(valueGiven) {
		srWriteValue(sr, writeValue);

		if(!noOutput)
			srUpdateOutput(sr);
	}

	return EXIT_SUCCESS;
}
