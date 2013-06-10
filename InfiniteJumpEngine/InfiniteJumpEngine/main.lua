argc = 0
args = { }
registryTable = { }

function registerObject( key, value ) 
	registryTable[key] = value
end

function printTable( )
	print (registryTable)
end

function getRegisteredObject( key )
	return registryTable[ key ]
end

function registerArg( value )
	args[argc] = value
	argc = argc + 1
	local out = ("Received argument:" .. value)
	print( out )
end

dofile("MiniGolf.lua")