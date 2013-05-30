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