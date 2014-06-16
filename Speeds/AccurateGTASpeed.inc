/*
	 Made by Gamer_Z & MP2
		This is actually the most accurate speed you will ever be able to approximate
		End-Users don't "feel" or "See" the speed is exponential, they just feel like it's the right speed.

	LICENSE:

	Copyright (c)  2013, Rafal "Gamer_Z" Grasman, MP2

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

/*
	Assuming:
		Bike		max speed = 25	MP/H (40  KM/H)
		Infernus	max speed = 110 MP/H (177 KM/H)
*/
forward Float:GetSpeedInMPH(Float:VelocityX,Float:VelocityY,Float:VelocityZ);
stock Float:GetSpeedInMPH(Float:VelocityX,Float:VelocityY,Float:VelocityZ)
{
	return (VelocityX*VelocityX+VelocityY*VelocityY+VelocityZ*VelocityZ)*(427833329/5871364);
}

forward Float:GetSpeedInKPH(Float:VelocityX,Float:VelocityY,Float:VelocityZ);
stock Float:GetSpeedInKPH(Float:VelocityX,Float:VelocityY,Float:VelocityZ)
{
	return (VelocityX*VelocityX+VelocityY*VelocityY+VelocityZ*VelocityZ)*(427833329/9449044);
}