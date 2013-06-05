hasPressed = false

function keyboard_cb( key )
	if key == 48 then
		registryTable["camera"]:switchProfile( 0 )
	elseif key == 49 then
		registryTable["camera"]:switchProfile( 1 )
	elseif key == 50 then
		registryTable["camera"]:switchProfile( 2 )
	elseif key == 51 then
		registryTable["camera"]:switchProfile( 3 )
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
	elseif key == 119 then
		registryTable["ball"]:sendMessage(registryTable["ball"], nil, "forward", 0,0,0,0);
	elseif key == 97 then
		registryTable["ball"]:sendMessage(registryTable["ball"], nil, "left", 0,0,0,0);
	elseif key == 115 then
		registryTable["ball"]:sendMessage(registryTable["ball"], nil, "back", 0,0,0,0);
	elseif key == 100 then
		registryTable["ball"]:sendMessage(registryTable["ball"], nil, "right", 0,0,0,0);
	else
	end
end

function mouseclick_cb( button, state, x, y )
	if state==1 and not hasPressed then
		clickPoint = vec3( x, 0, y )
		scaledX = ((2.0*x ) / ( 1280 )) - 1.0
		scaledY = ((-2.0*y ) / ( 720 )) + 1.0
		registryTable["arrowMesh"]:translate( scaledX, scaledY, 0 )
		hasPressed = true
	elseif state==0 and hasPressed then
		releasePoint = vec3( x, 0, y)
		dir = vec3( clickPoint.x - releasePoint.x, 0, clickPoint.z - releasePoint.z )
		normDir = normalize( dir.x, dir.y, dir.z )
		float len = length( dir.x, dir.y, dir.z )
		if len > 100 then
			dir.x = normDir.x * 3
			dir.y = normDir.y * 3
			dir.z = normDir.z * 3
		elseif len > 50 then
			dir.x = normDir.x * 2
			dir.y = normDir.y * 2
			dir.z = normDir.z * 2
		else
			dir.x = normDir.x
			dir.y = normDir.y
			dir.z = normDir.z
		end
		if length( dir.x, dir.y, dir.z ) > 0.07 then
			registryTable["ball"]:sendMessage(registryTable["ball"], nil, "shoot", vec4(dir.x, dir.y, dir.z, 0.0))
		end
		registryTable["arrowMesh"]:scale( 1.0, 1.0, 1.0 )
		axis = vec3( 0.0, 0.0, 1.0 )
		registryTable["arrowMesh"]:rotate( 0, axis )
		hasPressed = false
	end
end

function mousedrag_cb( x, y )

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

require( "main" )
require( "GolfAttributes" )