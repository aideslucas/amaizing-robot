/*
 * ConfigurationManager.h
 *
 *  Created on: Jun 3, 2016
 *      Author: colman
 */

#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_

#define LINE_TO_READ 100
#define PROPERITES_NUMBER 10

#include <string>

using namespace std;

class ConfigurationManager
{
	public:

		// Configuration constructor and destructor
		ConfigurationManager(const char* configurationPath);
		virtual ~ConfigurationManager();

		char fileInfo[PROPERITES_NUMBER][LINE_TO_READ];
		string map_path;
		int start_x;
		int start_y;
		int yaw;
		int target_x;
		int target_y;
		double robot_length;
		double robot_width;
		double map_resolution;
		double grid_resolution;
		char* configurationPath;

		void ReadConfigurationData(const char* configurationPath);
		void ReadConfigFile(const char* configPath);
		void Read(const char* configPath);
		void convertSizeToCM();
};

#endif /* CONFIGURATIONMANAGER_H_ */
