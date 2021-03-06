#pragma config(Motor,  motor1,          FL1,           tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor2,          FL2,           tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor5,          FR1,           tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor6,          FR2,           tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor7,          RL1,           tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor8,          RL2,           tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor11,         RR1,           tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor12,         RR2,           tmotorVexIQ, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//Terry stuff------------------------


int iOverallX =0;
int iOverallY =0;
int iOVerallW =0;
int anglemod = 0;


int CalcAngleTarget(int x,int y,int w,float xm,float ym){return radiansToDegrees(atan2(x+(w*xm),y+(w*ym))); }

int CalcSpeedTarget(int x,int y,int w,float xm,float ym){return sqrt(((y+(w*ym))*(y+(w*ym)))+(x+(w*xm))*(x+(w*xm)));}


void swerveTo(int modmot1, int modmot2,int angletarget, int speedtarget){

	int actualAngle=-getMotorEncoder(modmot1)+getMotorEncoder(modmot2);  //diff swerve
	//	int actualAngle=getMotorEncoder(modmot2); //regular swerve

	anglemod=(actualAngle/2)-angletarget;


	while (anglemod>180){anglemod -=360;}  //fix rollover
	while (anglemod<-180){anglemod +=360;}

	int revDir=1;													//use other side of motor if it requires less turning
	if (anglemod>90){
		anglemod-=180;
		revDir=-1;
	}
	if (anglemod<-90){
		anglemod+=180;
		revDir=-1;
	}

	setMotor(modmot1,(anglemod*2+speedtarget*revDir));  //diff swerve
	setMotor(modmot2,(-anglemod*2+speedtarget*revDir));

	// setMotor(modmot1,speedtarget*revDir) //regular swerve
	// setMotor(modmot2, anglemod)
}

task main(){

	while(1==1){
		iOverallX =(getJoystickValue(ChB)*.8);
		iOverallY =(getJoystickValue(ChA)*.8);
		iOVerallW =(getJoystickValue(ChC)*.8);

		swerveTo(FL1, FL2,CalcAngleTarget(iOverallX,iOverallY,iOVerallW,.5,.5)+0, CalcSpeedTarget(iOverallX,iOverallY,iOVerallW,.5,.5));
		swerveTo(FR1, FR2,CalcAngleTarget(iOverallX,iOverallY,iOVerallW,.5,-.5)+0, CalcSpeedTarget(iOverallX,iOverallY,iOVerallW,.5,-.5));
		swerveTo(RL1, RL2,CalcAngleTarget(iOverallX,iOverallY,iOVerallW,-.5,.5)+0, CalcSpeedTarget(iOverallX,iOverallY,iOVerallW,-.5,.5));
		swerveTo(RR1, RR2,CalcAngleTarget(iOverallX,iOverallY,iOVerallW,-.5,-.5)+0, CalcSpeedTarget(iOverallX,iOverallY,iOVerallW,-.5,-.5));
		//sleep(10);

}}
