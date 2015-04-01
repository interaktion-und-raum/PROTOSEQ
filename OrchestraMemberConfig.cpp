/**
 * @file    OrchestraMemberConfig
 * @author  David Beermann
 * @date    04/01/2015
 * @version 0.1
 * 
 * @brief Static class which contains the mapping from device MAC address to MIDI channel and klock meister setting
 */

#include "OrchestraMemberConfig.h"

void OrchestraMemberConfig::getDefaultConfig(orchestra_member_t* list) {
	list[0]  = { "04:E9:E5:01:16:C4", 8,  false };
	list[1]  = { "04:E9:E5:01:16:C3", 2,  false };
	list[2]  = { "04:E9:E5:01:16:A7", 3,  false };
	list[3]  = { "04:E9:E5:01:16:AA", 4,  false };
	list[4]  = { "04:E9:E5:01:16:9E", 5,  false };
	list[5]  = { "04:E9:E5:01:16:BE", 6,  false };
	list[6]  = { "04:E9:E5:00:E2:08", 7,  false };
	list[7]  = { "04:E9:E5:01:16:BD", 1,  true  };
	list[8]  = { "04:E9:E5:01:16:CD", 9,  false };
	list[9]  = { "04:E9:E5:01:16:A5", 10, false };
	list[10] = { "04:E9:E5:01:16:E7", 11, false };
}