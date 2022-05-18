#include "Waveshare_10Dof-D.h"
#include <time.h>

#define storage_file "/var/run/imu_data"
#define storage_file_tmp "/var/run/imu_data_tmp"


int main(int argc, char* argv[])
{
	IMU_EN_SENSOR_TYPE enMotionSensorType, enPressureType;
	IMU_ST_ANGLES_DATA stAngles;
	IMU_ST_SENSOR_DATA stGyroRawData;
	IMU_ST_SENSOR_DATA stAccelRawData;
	IMU_ST_SENSOR_DATA stMagnRawData;
	int32_t s32PressureVal = 0, s32TemperatureVal = 0, s32AltitudeVal = 0;

	imuInit(&enMotionSensorType, &enPressureType);
	if(IMU_EN_SENSOR_TYPE_ICM20948 == enMotionSensorType)
	{
		printf("Motion sersor is ICM-20948\n" );
	}
	else
	{
		printf("Motion sersor NULL\n");
	}
	if(IMU_EN_SENSOR_TYPE_BMP280 == enPressureType)
	{
		printf("Pressure sersor is BMP280\n");
	}
	else
	{
		printf("Pressure sersor NULL\n");
	}

	while(1)
	{
		imuDataGet( &stAngles, &stGyroRawData, &stAccelRawData, &stMagnRawData);
		pressSensorDataGet(&s32TemperatureVal, &s32PressureVal, &s32AltitudeVal);

		FILE *tmp_storage_file = fopen(storage_file_tmp, "w");
		if (tmp_storage_file == NULL) {
			printf("Unable to open temporary file\n");
			return 1;
		}
		fprintf(tmp_storage_file, "roll=%f pitch=%f yaw=%f alt=%f temp=%f time=%u\n", 
			stAngles.fRoll, stAngles.fPitch, stAngles.fYaw, 
			(float)s32AltitudeVal/100, (float)s32TemperatureVal/100,
			(unsigned)time(NULL)); 
		fsync((int)tmp_storage_file);
		fclose(tmp_storage_file);
		rename(storage_file_tmp, storage_file);
		delay(100);
	}
	return 0;
}
