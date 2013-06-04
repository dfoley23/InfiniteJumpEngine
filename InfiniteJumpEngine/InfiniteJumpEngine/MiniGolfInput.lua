
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

end

function mouseclick_cb( button, state, x, y )
	if state==1 and not hasPressed then
		clickPoint = vec3( x, 0, y )
		scaledX = ((2.0*x ) / ( 1280 )) - 1.0
		scaledY = ((-2.0*y ) / ( 720 )) + 1.0
		registryTable["ballDirHud"]:translate( scaledX, scaledY, 0 )
		hasPressed = true
	elseif state==0 and hasPressed then
		releasePoint = vec3( x, 0, y)
		dir = vec3( clickPoint.x - releasePoint.x, 0, clickPoint.z - releasePoint.z )
		if length( dir.x, dir.y, dir.z ) > 100 then
			dir = vec3( normalizeVec( dir.x * 3.0, dir.y * 3.0, dir.z * 3.0 ) )
		elseif length( dir.x, dir.y, dir.z ) > 50 then
			dir = vec3( normalizeVec( dir.x * 2.0, dir.y * 2.0, dir.z * 2.0 ) )
		else
			dir = vec3( normalizeVec( dir.x, dir.y, dir.z ) )
		end
		if length( dir.x, dir.y, dir.z ) > 0.07 then
			registryTable["ball"]:sendMessage(registryTable["ball"], nil, "shoot", vec4(dir.x, dir.y, dir.z, 0.0))
		end
		registryTable["ballDirHud"]:scale( 1.0, 1.0, 1.0 )
		axis = vec3( 0.0, 0.0, 1.0 )
		registryTable["ballDirHud"]:rotate( 0, axis )
		hasPressed = false
	end
end

function mousedrag_cb( x, y )

end

function mousewheel_cb( wheel, direction, x, y )

end

requires( "main" )