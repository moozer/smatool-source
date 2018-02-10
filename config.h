/*
 * config .h
 *
 *  Created on: Feb 10, 2018
 *      Author: moz
 */

#ifndef CONFIG_H_
#define CONFIG_H_

typedef struct {
	char Inverter[20]; /*--inverter 	-i 	*/
	char BTAddress[20]; /*--address  	-a 	*/
	int bt_timeout; /*--timeout  	-t 	*/
	char Password[20]; /*--password 	-p 	*/
	char Config[80]; /*--config   	-c 	*/
	char File[80]; /*--file     	-f 	*/
	float latitude_f; /*--latitude  	-la 	*/
	float longitude_f; /*--longitude 	-lo 	*/
	char PVOutputURL[80]; /*--pvouturl    -url 	*/
	char PVOutputKey[80]; /*--pvoutkey    -key 	*/
	char PVOutputSid[20]; /*--pvoutsid    -sid 	*/
	char Setting[80]; /*inverter model data*/
	unsigned char InverterCode[4]; /*Unknown code inverter specific*/
	unsigned int ArchiveCode; /* Code for archive data */
} ConfType;

void PrintHelp();

int ReadCommandConfig(ConfType *conf, int argc, char **argv, char * datefrom,
		char * dateto, int * verbose, int * repost, int * test, int * install,
		int * update);

int GetInverterSetting(ConfType *conf);

int GetConfig(ConfType *conf);

void InitConfig(ConfType *conf, char * datefrom, char * dateto);

#endif /* CONFIG_H_ */
