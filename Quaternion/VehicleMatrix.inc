/*
	 Made by Gamer_Z
		Provides vehicle offset functions and vehicle matrix functions for easier workflow with positioning tied to vehicle rotation.

	LICENSE:

	Copyright (c)  2013, Rafal "Gamer_Z" Grasman

	All rights reserved.

	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

		-Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
		-Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
		-Neither the name of the organization nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

		Special Clause for SA-MP Servers:
		-The authors and or contributors must be credited in a visible and accessible area for the player, including but not limited to: about boxes, welcome messages on the server, commands displaying messages and/or message boxes

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR  CONSEQUENTIAL
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <a_samp>

enum MatrixParts
{
	mp_PITCH,
	mp_ROLL,
	mp_YAW,
	mp_POS
};

enum MatrixIndicator
{
	Float:mi_X,
	Float:mi_Y,
	Float:mi_Z
};

/*
	Get Corresponding GTA {{Internal}} Vehicle Matrix
*/
//aka quaternion to matrix conversion + including position
stock GetVehicleMatrix(vehicleid,Mat4x3[MatrixParts][MatrixIndicator])
{
//initial processing step - gathering information
	new
		Float:x,
		Float:y,
		Float:z,
		Float:w,
		Float:Pos[3];

	GetVehicleRotationQuat(vehicleid,w,x,y,z);
	GetVehiclePos(vehicleid,Pos[0],Pos[1],Pos[2]);

//initialized math for quaternion to matrix conversion {for sake of simplicity and efficiency}
	new
		Float:x2 = x * x,
	 	Float:y2 = y * y,
	 	Float:z2 = z * z,
	 	Float:xy = x * y,
	 	Float:xz = x * z,
		Float:yz = y * z,
		Float:wx = w * x,
		Float:wy = w * y,
		Float:wz = w * z;

//the maths required to convert a quat to a matrix
	Mat4x3[mp_PITCH][mi_X] = 1.0 - 2.0 * (y2 + z2);
	Mat4x3[mp_PITCH][mi_Y] = 2.0 * (xy - wz);
	Mat4x3[mp_PITCH][mi_Z] = 2.0 * (xz + wy);
	Mat4x3[mp_ROLL][mi_X] = 2.0 * (xy + wz);
	Mat4x3[mp_ROLL][mi_Y] = 1.0 - 2.0 * (x2 + z2);
	Mat4x3[mp_ROLL][mi_Z] = 2.0 * (yz - wx);
 	Mat4x3[mp_YAW][mi_X] = 2.0 * (xz - wy);
 	Mat4x3[mp_YAW][mi_Y] = 2.0 * (yz + wx);
 	Mat4x3[mp_YAW][mi_Z] = 1.0 - 2.0 * (x2 + y2);
//the gta vehicle matrix has the position in it, I want it to keep just like GTA does so I put the position in
  	Mat4x3[mp_POS][mi_X] = Pos[0];
  	Mat4x3[mp_POS][mi_Y] = Pos[1];
  	Mat4x3[mp_POS][mi_Z] = Pos[2];
  	
	return 1;
}

/*
	Get position offset at position corresponding to the correct vehicle rotation
*/
stock PositionFromVehicleOffset(vehicle,Float:offX,Float:offY,Float:offZ,&Float:x,&Float:y,&Float:z)
{
//initial processing step - gather information
	new
		Mat4x3[MatrixParts][MatrixIndicator];

    GetVehicleMatrix(vehicle,Mat4x3);

//offset calculation math
	x = offX * Mat4x3[mp_PITCH][mi_X] + offY * Mat4x3[mp_ROLL][mi_X] + offZ * Mat4x3[mp_YAW][mi_X] + Mat4x3[mp_POS][mi_X];
	y = offX * Mat4x3[mp_PITCH][mi_Y] + offY * Mat4x3[mp_ROLL][mi_Y] + offZ * Mat4x3[mp_YAW][mi_Y] + Mat4x3[mp_POS][mi_Y];
	z = offX * Mat4x3[mp_PITCH][mi_Z] + offY * Mat4x3[mp_ROLL][mi_Z] + offZ * Mat4x3[mp_YAW][mi_Z] + Mat4x3[mp_POS][mi_Z];

	return 1;
}
