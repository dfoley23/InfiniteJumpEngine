registryTable = { }
clickPoint
hasPressed = false

function registerObject( key, value ) 
	registryTable[key] = value
end

function registerComponent( key, value )
	registryTable[key] = Component( value );
end

function printTable( )
	print (registryTable)
end

function getRegisteredObject( key )
	return registryTable[ key ]
end

function keyboard_cb( key )
	
end

function spec_keyboard_cb( key )

end

function mouseclick_cb( button, state, x, y )
	if state==1 && !hasPressed then
		clickPoint = vec3( x, 0, y )
		scaledX = ((2.0*x ) / ( getWinWidth() )) - 1.0
		scaledY = ((-2.0*y ) / ( getWinHeight() )) + 1.0
		registry["ballDirHud"]:translate( scaledX, scaledY, 0 )
		hasPressed = true
	elseif state==0 && hasPressed
		releasePoint = vec3( x, 0, y)
		dir = -( releasePoint - clickPoint )
		if length( dir ) > 100
			dir = normalize( dir ) * 3.0
		elseif length( dir ) > 50
			dir = normalize( dir ) * 2.0
		else
			dir = normalize( dir )
		end
		if length( dir ) > 0.07
			registry["ball"]:sendMessage(registry["ball"], NULL, "shoot", vec4(dir.x, dir.y, dir.z, 0.f))
		end
		registry["ballDirHud"]:scale( 1, 1, 1 )
		registry["ballDirHud"]:rotate( 0, glm::vec3( 0, 0, 1 ) )
		hasPressed = false
	end
end

function mousedrag_cb( x, y )
	
end

function mousewheel_cb( wheel, direction, x, y )

end