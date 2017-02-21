#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    settingKnob,    sensorPotentiometer)
#pragma config(Sensor, dgtl1,  leftBtn,        sensorTouch)
#pragma config(Sensor, dgtl2,  rightBtn,       sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           release,       tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftDrive,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           rightDrive,    tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int driveSpeed = 80;
int turnSpeed = 127;
int releaseSpeed = 127;
int breakValue = 3;
int turnValue = 670;
int oneMetre = 4800;


task main()
{
	while(1){
		// mode drive
		if(SensorValue[settingKnob] < 2000){
			if(SensorValue[leftBtn]){
				//forward
				nMotorEncoder[rightDrive] = 0;
				while(nMotorEncoder[rightDrive] < oneMetre){
					motor[leftDrive] = driveSpeed;
					motor[rightDrive] = driveSpeed;
				}
				motor[leftDrive] = -breakValue;
				motor[rightDrive] = -breakValue;
				wait1Msec(100);
				motor[leftDrive] = 0;
				motor[rightDrive] = 0;

			} else if(SensorValue[rightBtn]){
				//rotate 90 degrees
				nMotorEncoder[rightDrive] = 0;
				while(nMotorEncoder[rightDrive] < turnValue){
					motor[leftDrive] = -turnSpeed;
					motor[rightDrive] = turnSpeed;
				}
				motor[leftDrive] = breakValue;
				motor[rightDrive] = -breakValue;
				wait1Msec(300);
				motor[leftDrive] = 0;
				motor[rightDrive] = 0;
			} else {
				//default state
				motor[leftDrive] = 0;
				motor[rightDrive] = 0;
			}
		// mode release
		} else if(SensorValue[settingKnob] > 2000){
			if(SensorValue[leftBtn]){
				motor[release] = 70;
			} else if(SensorValue[rightBtn]){
				motor[release] = -releaseSpeed;
				wait1Msec(2000);
				motor[release] = 0;
			} else {
				motor[release] = 0;
			}
		}
	}
}
