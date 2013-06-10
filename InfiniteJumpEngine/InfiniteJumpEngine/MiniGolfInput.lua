hasPressed = false
clickPointX = 0
clickPointY = 0
releasePointX = 0
releasePointY = 0
dragPointX = 0
dragPointY = 0

dofile( "GolfAttributes.lua" )

function keyboard_cb( key )
	if key == 48 then --0
		camProfile = 0
	elseif key == 49 then --1
		camProfile = 1
	elseif key == 50 then --2
		camProfile = 2
	elseif key == 51 then --3
		camProfile = 3
	elseif key == 119 then --w
		registryTable["ball"]:sendMessage(registryTable["ball"], registryTable["ball"], "forward", 0.0,0.0,0.0,0.0);
	elseif key == 97 then --a
		registryTable["ball"]:sendMessage(registryTable["ball"], registryTable["ball"], "left", 0.0,0.0,0.0,0.0);
	elseif key == 115 then --s
		registryTable["ball"]:sendMessage(registryTable["ball"], registryTable["ball"], "back", 0.0,0.0,0.0,0.0);
	elseif key == 100 then --d
		registryTable["ball"]:sendMessage(registryTable["ball"], registryTable["ball"], "right", 0.0,0.0,0.0,0.0);
	else
	end
end

function spec_keyboard_cb( key )
	if key == 102 then
		eyePosX = eyePosX + 1
		registryTable["camera"]:changeEyePos( eyePosX, eyePosY, eyePosZ )
	elseif key == 100 then
		eyePosX = eyePosX - 1
		registryTable["camera"]:changeEyePos( eyePosX, eyePosY, eyePosZ )
	elseif key == 101 then
		eyePosY= eyePosY + 1
		registryTable["camera"]:changeEyePos( eyePosX, eyePosY, eyePosZ )
	elseif key == 103 then
		eyePosY= eyePosY - 1
		registryTable["camera"]:changeEyePos( eyePosX, eyePosY, eyePosZ )
	else
	end
end

function mouseclick_cb( button, state, x, y )
	if button==0 then
		if state==0 then
			clickPointX = x
			clickPointY = y
			scaledX = ((2.0*x ) / ( 1280.0 )) - 1.0
			scaledY = ((-2.0*y ) / ( 720.0 )) + 1.0
			registryTable["arrowMesh"]:translate( scaledX, scaledY, 0 )
		elseif state==1 then
			releasePointX = x
			releasePointY = y
			dir = vec3( clickPointX - releasePointX, 0, clickPointY - releasePointY )
			normDir = normalize( dir.x, dir.y, dir.z )
			len = length( dir.x, dir.y, dir.z )
			if len > 100 then
				dir.x = normDir.x * hardShot
				dir.y = normDir.y * hardShot
				dir.z = normDir.z * hardShot
			elseif len > 50 then
				dir.x = normDir.x * softShot
				dir.y = normDir.y * softShot
				dir.z = normDir.z * softShot
			else
				dir.x = normDir.x
				dir.y = normDir.y
				dir.z = normDir.z
			end
			if length( dir.x, dir.y, dir.z ) > 0.07 then
				registryTable["ball"]:sendMessage(registryTable["ball"], registryTable["ball"], "shoot", dir.x, dir.y, dir.z, 0)
			end
			registryTable["arrowMesh"]:scale( 1.0, 1.0, 1.0 )
			registryTable["arrowMesh"]:rotate( 0, 0, 0, 1 )
		end
	end
end

function mousedrag_cb( x, y )
	curPosX = registryTable["arrowMesh"]:getCenter().x
	curPosY = registryTable["arrowMesh"]:getCenter().y
	dragPointX = x
	dragPointY = y
	scaledX = ((arrowScale*x ) / ( 1280.0 )) - (arrowScale/2.0)
	scaledY = ((arrowScale*y ) / ( 720.0 )) - (arrowScale/2.0)
	dy = curPosY-scaledY
	if dy < 0 then
		dy = -dy
	end
	dx = curPosX-scaledX
	if dx < 0 then
		dx = -dx
	end
	if dy > 0 then
		scaleNum = 1+dy
		registryTable["arrowMesh"]:scale( 1, scaleNum, 1 )
		dir = normalize(clickPointX - dragPointX, 0, clickPointY - dragPointY )
		cosineTheta = dot( dir.x, dir.y, dir.z, 0, 0, -1)
		angle = acos( cosineTheta )
		if x > clickPointX then
			angle = -angle
		end
		registryTable["arrowMesh"]:rotate( angle*rad_to_deg, 0, 0, -1 )
	elseif dx > 0 then
		scaleNum = 1+dx
		registryTable["arrowMesh"]:scale( scaleNum, 1, 1 )
		dir = normalize(clickPointX - dragPointX, 0, clickPointY - dragPointY )
		cosineTheta = dot( dir.x, dir.y, dir.z, 0, 0, -1)
		angle = acos( cosineTheta )
		if x > clickPointX then
			angle = -angle;
		end
		registryTable["arrowMesh"]:rotate( angle*rad_to_deg, 0, 0, -1 )
	end
end

function mousewheel_cb( wheel, direction, x, y )
	if direction > 0 then
		eyePosZ = eyePosZ - 1
		registryTable["camera"]:changeEyePos( eyePosX, eyePosY, eyePosZ )
	else 
		eyePosZ = eyePosZ + 1
		registryTable["camera"]:changeEyePos( eyePosX, eyePosY, eyePosZ )
	end
end