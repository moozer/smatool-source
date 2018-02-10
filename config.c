/*
 * config.c
 *
 *  Created on: Feb 10, 2018
 *      Author: moz
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

/* Print a help message */
void PrintHelp() {
	printf("Usage: smatool [OPTION]\n");
	printf(
			"  -v,  --verbose                           Give more verbose output\n");
	printf(
			"  -c,  --config CONFIGFILE                 Set config file default smatool.conf\n");
	printf(
			"       --test                              Run in test mode - don't update data\n");
	printf("\n");
	printf("Dates are no longer required - defaults to 2000 to now\n");
	printf("  -from  --datefrom YYYY-DD-MM HH:MM:00    Date range from date\n");
	printf("  -to  --dateto YYYY-DD-MM HH:MM:00        Date range to date\n");
	printf("\n");
	printf("The following options are in config file but may be overridden\n");
	printf("  -i,  --inverter INVERTER_MODEL           inverter model\n");
	printf("  -a,  --address INVERTER_ADDRESS          inverter BT address\n");
	printf(
			"  -t,  --timeout TIMEOUT                   bluetooth timeout (secs) default 5\n");
	printf(
			"  -p,  --password PASSWORD                 inverter user password default 0000\n");
	printf(
			"  -f,  --file FILENAME                     command file default sma.in.new\n");
	printf("queried in the dark\n");
	printf(
			"  -lat,  --latitude LATITUDE               location latitude -180 to 180 deg\n");
	printf(
			"  -lon,  --longitude LONGITUDE             location longitude -90 to 90 deg\n");
	printf("PVOutput.org (A free solar information system) Configs\n");
	printf(
			"  -url,  --pvouturl PVOUTURL               pvoutput.org live url\n");
	printf("  -key,  --pvoutkey PVOUTKEY               pvoutput.org key\n");
	printf("  -sid,  --pvoutsid PVOUTSID               pvoutput.org sid\n");
	printf(
			"  -repost                                  verify and repost data if different\n");
	printf("\n\n");
}




/* Init Config to default values */
int ReadCommandConfig(ConfType *conf, int argc, char **argv, char * datefrom,
		char * dateto, int * verbose, int * repost, int * test, int * install,
		int * update) {
	int i;

	// these need validation checking at some stage TODO
	for (i = 1; i < argc; i++)			//Read through passed arguments
			{
		if ((strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "--verbose") == 0))
			(*verbose) = 1;
		else if ((strcmp(argv[i], "-c") == 0)
				|| (strcmp(argv[i], "--config") == 0)) {
			i++;
			if (i < argc) {
				strcpy(conf->Config, argv[i]);
			}
		} else if (strcmp(argv[i], "--test") == 0)
			(*test) = 1;
		else if ((strcmp(argv[i], "-from") == 0)
				|| (strcmp(argv[i], "--datefrom") == 0)) {
			i++;
			if (i < argc) {
				strcpy(datefrom, argv[i]);
			}
		} else if ((strcmp(argv[i], "-to") == 0)
				|| (strcmp(argv[i], "--dateto") == 0)) {
			i++;
			if (i < argc) {
				strcpy(dateto, argv[i]);
			}
		}
		// never repost'ing
		//else if (strcmp(argv[i],"-repost")==0){
		//    i++;
		//        (*repost)=1;
		//}
		else if ((strcmp(argv[i], "-i") == 0)
				|| (strcmp(argv[i], "--inverter") == 0)) {
			i++;
			if (i < argc) {
				strcpy(conf->Inverter, argv[i]);
			}
		} else if ((strcmp(argv[i], "-a") == 0)
				|| (strcmp(argv[i], "--address") == 0)) {
			i++;
			if (i < argc) {
				strcpy(conf->BTAddress, argv[i]);
			}
		} else if ((strcmp(argv[i], "-t") == 0)
				|| (strcmp(argv[i], "--timeout") == 0)) {
			i++;
			if (i < argc) {
				conf->bt_timeout = atoi(argv[i]);
			}
		} else if ((strcmp(argv[i], "-p") == 0)
				|| (strcmp(argv[i], "--password") == 0)) {
			i++;
			if (i < argc) {
				strcpy(conf->Password, argv[i]);
			}
		} else if ((strcmp(argv[i], "-f") == 0)
				|| (strcmp(argv[i], "--file") == 0)) {
			i++;
			if (i < argc) {
				strcpy(conf->File, argv[i]);
			}
		} else if ((strcmp(argv[i], "-lat") == 0)
				|| (strcmp(argv[i], "--latitude") == 0)) {
			i++;
			if (i < argc) {
				conf->latitude_f = atof(argv[i]);
			}
		} else if ((strcmp(argv[i], "-long") == 0)
				|| (strcmp(argv[i], "--longitude") == 0)) {
			i++;
			if (i < argc) {
				conf->longitude_f = atof(argv[i]);
			}
		} else if ((strcmp(argv[i], "-url") == 0)
				|| (strcmp(argv[i], "--pvouturl") == 0)) {
			i++;
			if (i < argc) {
				strcpy(conf->PVOutputURL, argv[i]);
			}
		} else if ((strcmp(argv[i], "-key") == 0)
				|| (strcmp(argv[i], "--pvoutkey") == 0)) {
			i++;
			if (i < argc) {
				strcpy(conf->PVOutputKey, argv[i]);
			}
		} else if ((strcmp(argv[i], "-sid") == 0)
				|| (strcmp(argv[i], "--pvoutsid") == 0)) {
			i++;
			if (i < argc) {
				strcpy(conf->PVOutputSid, argv[i]);
			}
		} else if ((strcmp(argv[i], "-h") == 0)
				|| (strcmp(argv[i], "--help") == 0)) {
			PrintHelp();
			return (-1);
		} else if (strcmp(argv[i], "--INSTALL") == 0)
			(*install) = 1;
		else if (strcmp(argv[i], "--UPDATE") == 0)
			(*update) = 1;
		else {
			printf("Bad Syntax\n\n");
			for (i = 0; i < argc; i++)
				printf("%s ", argv[i]);
			printf("\n\n");

			PrintHelp();
			return (-1);
		}
	}
	return (0);
}

/* Init Config to default values */
void InitConfig(ConfType *conf, char * datefrom, char * dateto) {
	strcpy(conf->Config, "./smatool.conf");
	strcpy(conf->Setting, "./invcode.in");
	strcpy(conf->Inverter, "");
	strcpy(conf->BTAddress, "");
	conf->bt_timeout = 30;
	strcpy(conf->Password, "0000");
	strcpy(conf->File, "sma.in.new");
	conf->latitude_f = 999;
	conf->longitude_f = 999;
	strcpy(conf->PVOutputURL, "http://pvoutput.org/service/r2/addstatus.jsp");
	strcpy(conf->PVOutputKey, "");
	strcpy(conf->PVOutputSid, "");
	conf->InverterCode[0] = 0;
	conf->InverterCode[1] = 0;
	conf->InverterCode[2] = 0;
	conf->InverterCode[3] = 0;
	conf->ArchiveCode = 0;
	strcpy(datefrom, "");
	strcpy(dateto, "");
}

/* read Config from file */
int GetConfig(ConfType *conf) {
	FILE *fp;
	char line[400];
	char variable[400];
	char value[400];

	if (strlen(conf->Config) > 0) {
		if ((fp = fopen(conf->Config, "r")) == (FILE *) NULL) {
			printf("Error! Could not open file %s\n", conf->Config);
			return (-1); //Could not open file
		}
	} else {
		if ((fp = fopen("./smatool.conf", "r")) == (FILE *) NULL) {
			printf("Error! Could not open file ./smatool.conf\n");
			return (-1); //Could not open file
		}
	}
	while (!feof(fp)) {
		if (fgets(line, 400, fp) != NULL) {		//read line from smatool.conf
			if (line[0] != '#') {
				strcpy(value, ""); //Null out value
				sscanf(line, "%s %s", variable, value);
				if (value[0] != '\0') {
					if (strcmp(variable, "Inverter") == 0)
						strcpy(conf->Inverter, value);
					if (strcmp(variable, "BTAddress") == 0)
						strcpy(conf->BTAddress, value);
					if (strcmp(variable, "BTTimeout") == 0)
						conf->bt_timeout = atoi(value);
					if (strcmp(variable, "Password") == 0)
						strcpy(conf->Password, value);
					if (strcmp(variable, "File") == 0)
						strcpy(conf->File, value);
					if (strcmp(variable, "Latitude") == 0)
						conf->latitude_f = atof(value);
					if (strcmp(variable, "Longitude") == 0)
						conf->longitude_f = atof(value);
					if (strcmp(variable, "PVOutputURL") == 0)
						strcpy(conf->PVOutputURL, value);
					if (strcmp(variable, "PVOutputKey") == 0)
						strcpy(conf->PVOutputKey, value);
					if (strcmp(variable, "PVOutputSid") == 0)
						strcpy(conf->PVOutputSid, value);
				}
			}
		}
	}
	fclose(fp);
	return (0);
}

/* read  Inverter Settings from file */
int GetInverterSetting(ConfType *conf) {
	FILE *fp;
	char line[400];
	char variable[400];
	char value[400];
	int found_inverter = 0;

	if (strlen(conf->Setting) > 0) {
		if ((fp = fopen(conf->Setting, "r")) == (FILE *) NULL) {
			printf("Error! Could not open file %s\n", conf->Setting);
			return (-1); //Could not open file
		}
	} else {
		if ((fp = fopen("./invcode.in", "r")) == (FILE *) NULL) {
			printf("Error! Could not open file ./invcode.in\n");
			return (-1); //Could not open file
		}
	}
	while (!feof(fp)) {
		if (fgets(line, 400, fp) != NULL) {		//read line from smatool.conf
			if (line[0] != '#') {
				strcpy(value, ""); //Null out value
				sscanf(line, "%s %s", variable, value);
				if (value[0] != '\0') {
					if (strcmp(variable, "Inverter") == 0) {
						if (strcmp(value, conf->Inverter) == 0)
							found_inverter = 1;
						else
							found_inverter = 0;
					}
					if ((strcmp(variable, "Code1") == 0) && found_inverter) {
						sscanf(value, "%X", &conf->InverterCode[0]);
					}
					if ((strcmp(variable, "Code2") == 0) && found_inverter)
						sscanf(value, "%X", &conf->InverterCode[1]);
					if ((strcmp(variable, "Code3") == 0) && found_inverter)
						sscanf(value, "%X", &conf->InverterCode[2]);
					if ((strcmp(variable, "Code4") == 0) && found_inverter)
						sscanf(value, "%X", &conf->InverterCode[3]);
					if ((strcmp(variable, "InvCode") == 0) && found_inverter)
						sscanf(value, "%X", &conf->ArchiveCode);
				}
			}
		}
	}
	fclose(fp);
	if ((conf->InverterCode[0] == 0) || (conf->InverterCode[1] == 0)
			|| (conf->InverterCode[2] == 0) || (conf->InverterCode[3] == 0)
			|| (conf->ArchiveCode == 0)) {
		printf("\n Error ! not all codes set\n");
		fclose(fp);
		return (-1);
	}
	return (0);
}


