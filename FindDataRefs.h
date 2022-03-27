#include "XPLMDataAccess.h"


float FindDataRefs(float          inElapsedSinceLastCall,
	float                inElapsedTimeSinceLastFlightLoop,
	int                  inCounter,
	void* time)
{
	
	//CPT FMC
	lines1[0] = XPLMFindDataRef("laminar/B738/fmc1/Line00_L");
	lines1[1] = XPLMFindDataRef("laminar/B738/fmc1/Line01_L");
	lines1[2] = XPLMFindDataRef("laminar/B738/fmc1/Line02_L");
	lines1[3] = XPLMFindDataRef("laminar/B738/fmc1/Line03_L");
	lines1[4] = XPLMFindDataRef("laminar/B738/fmc1/Line04_L");
	lines1[5] = XPLMFindDataRef("laminar/B738/fmc1/Line05_L");
	lines1[6] = XPLMFindDataRef("laminar/B738/fmc1/Line06_L");
	lines1[7] = XPLMFindDataRef("laminar/B738/fmc1/Line_entry");
	lines1[8] = XPLMFindDataRef("laminar/B738/fmc1/Line00_S");
	lines1[9] = XPLMFindDataRef("laminar/B738/fmc1/Line01_X");
	lines1[10] = XPLMFindDataRef("laminar/B738/fmc1/Line02_X");
	lines1[11] = XPLMFindDataRef("laminar/B738/fmc1/Line03_X");
	lines1[12] = XPLMFindDataRef("laminar/B738/fmc1/Line04_X");
	lines1[13] = XPLMFindDataRef("laminar/B738/fmc1/Line05_X");
	lines1[14] = XPLMFindDataRef("laminar/B738/fmc1/Line06_X");
	lines1[15] = XPLMFindDataRef("laminar/B738/fmc1/Line01_S");
	lines1[16] = XPLMFindDataRef("laminar/B738/fmc1/Line02_S");
	lines1[17] = XPLMFindDataRef("laminar/B738/fmc1/Line03_S");
	lines1[18] = XPLMFindDataRef("laminar/B738/fmc1/Line04_S");
	lines1[19] = XPLMFindDataRef("laminar/B738/fmc1/Line05_S");
	lines1[20] = XPLMFindDataRef("laminar/B738/fmc1/Line06_S");
	lines1[21] = XPLMFindDataRef("laminar/B738/fmc1/Line00_M");
	lines1[22] = XPLMFindDataRef("laminar/B738/fmc1/Line01_M");
	lines1[23] = XPLMFindDataRef("laminar/B738/fmc1/Line02_M");
	lines1[24] = XPLMFindDataRef("laminar/B738/fmc1/Line03_M");
	lines1[25] = XPLMFindDataRef("laminar/B738/fmc1/Line04_M");
	lines1[26] = XPLMFindDataRef("laminar/B738/fmc1/Line05_M");
	lines1[27] = XPLMFindDataRef("laminar/B738/fmc1/Line06_M");
	lines1[28] = XPLMFindDataRef("laminar/B738/fmc1/Line00_G");
	lines1[29] = XPLMFindDataRef("laminar/B738/fmc1/Line01_G");
	lines1[30] = XPLMFindDataRef("laminar/B738/fmc1/Line02_G");
	lines1[31] = XPLMFindDataRef("laminar/B738/fmc1/Line03_G");
	lines1[32] = XPLMFindDataRef("laminar/B738/fmc1/Line04_G");
	lines1[33] = XPLMFindDataRef("laminar/B738/fmc1/Line05_G");
	lines1[34] = XPLMFindDataRef("laminar/B738/fmc1/Line06_G");
	lines1[35] = XPLMFindDataRef("laminar/B738/fmc1/Line06_LX");


	//FO FMC

	lines2[0] = XPLMFindDataRef("laminar/B738/fmc2/Line00_L");
	lines2[1] = XPLMFindDataRef("laminar/B738/fmc2/Line01_L");
	lines2[2] = XPLMFindDataRef("laminar/B738/fmc2/Line02_L");
	lines2[3] = XPLMFindDataRef("laminar/B738/fmc2/Line03_L");
	lines2[4] = XPLMFindDataRef("laminar/B738/fmc2/Line04_L");
	lines2[5] = XPLMFindDataRef("laminar/B738/fmc2/Line05_L");
	lines2[6] = XPLMFindDataRef("laminar/B738/fmc2/Line06_L");
	lines2[7] = XPLMFindDataRef("laminar/B738/fmc2/Line_entry");
	lines2[8] = XPLMFindDataRef("laminar/B738/fmc2/Line00_S");
	lines2[9] = XPLMFindDataRef("laminar/B738/fmc2/Line01_X");
	lines2[10] = XPLMFindDataRef("laminar/B738/fmc2/Line02_X");
	lines2[11] = XPLMFindDataRef("laminar/B738/fmc2/Line03_X");
	lines2[12] = XPLMFindDataRef("laminar/B738/fmc2/Line04_X");
	lines2[13] = XPLMFindDataRef("laminar/B738/fmc2/Line05_X");
	lines2[14] = XPLMFindDataRef("laminar/B738/fmc2/Line06_X");
	lines2[15] = XPLMFindDataRef("laminar/B738/fmc2/Line01_S");
	lines2[16] = XPLMFindDataRef("laminar/B738/fmc2/Line02_S");
	lines2[17] = XPLMFindDataRef("laminar/B738/fmc2/Line03_S");
	lines2[18] = XPLMFindDataRef("laminar/B738/fmc2/Line04_S");
	lines2[19] = XPLMFindDataRef("laminar/B738/fmc2/Line05_S");
	lines2[20] = XPLMFindDataRef("laminar/B738/fmc2/Line06_S");
	lines2[21] = XPLMFindDataRef("laminar/B738/fmc2/Line00_M");
	lines2[22] = XPLMFindDataRef("laminar/B738/fmc2/Line01_M");
	lines2[23] = XPLMFindDataRef("laminar/B738/fmc2/Line02_M");
	lines2[24] = XPLMFindDataRef("laminar/B738/fmc2/Line03_M");
	lines2[25] = XPLMFindDataRef("laminar/B738/fmc2/Line04_M");
	lines2[26] = XPLMFindDataRef("laminar/B738/fmc2/Line05_M");
	lines2[27] = XPLMFindDataRef("laminar/B738/fmc2/Line06_M");
	lines2[28] = XPLMFindDataRef("laminar/B738/fmc2/Line00_G");
	lines2[29] = XPLMFindDataRef("laminar/B738/fmc2/Line01_G");
	lines2[30] = XPLMFindDataRef("laminar/B738/fmc2/Line02_G");
	lines2[31] = XPLMFindDataRef("laminar/B738/fmc2/Line03_G");
	lines2[32] = XPLMFindDataRef("laminar/B738/fmc2/Line04_G");
	lines2[33] = XPLMFindDataRef("laminar/B738/fmc2/Line05_G");
	lines2[34] = XPLMFindDataRef("laminar/B738/fmc2/Line06_G");
	lines2[35] = XPLMFindDataRef("laminar/B738/fmc2/Line06_LX");

	execLight = XPLMFindDataRef("laminar/B738/indicators/fmc_exec_lights");
	msgLight = XPLMFindDataRef("laminar/B738/fmc/fmc_message");

	execLightFo = XPLMFindDataRef("laminar/B738/indicators/fmc_exec_lights_fo");
	msgLightFo = XPLMFindDataRef("laminar/B738/fmc/fmc_message2");

	tdDistance = XPLMFindDataRef("laminar/B738/fms/vnav_td_dist");

	if (lines1[0] == NULL) {
		return 0.05;
	}
	else {
		return 0;
	}

}