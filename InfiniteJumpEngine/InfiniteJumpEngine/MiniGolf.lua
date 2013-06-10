
rad_to_deg = 57.2957795131

dofile( "GolfAttributes.lua" )
dofile( "MiniGolfInput.lua" )

function init()

end

profile = "Profiles/default.sav"

function loadDefaultScene()
	--Define Root
	--root = ComponentContainer.__init()
	
	--Define Camera
	--camera = Camera.__init()
	
	--Define Course
	local hole = 0
	local filename = "Levels/course.db"
	if argc > 1 then 
		filename = argv[1]
		if argc > 2 then
			hole = argv[2]
			if argc > 3 then
				profile = argv[3]
			end
		end
	end
	print ("Filename:" .. filename)
	print ("Hole:" .. hole)
	print ("Profile:" .. profile)
	local courseFile = io.open(filename, "r")
	if courseFile ~= nil then
		print ("(Lua)Successfully opened courses:" .. filename)
	else
		print ("(Lua)Failed to open courses:" .. filename)
	end
	--require(GolfHoleSelector)
	--course = GolfHoleSelector.__init(filename, hole)
	
	--Define HUD
	--hudRoot = GolfHud.init()
	--hudGLUI = GLUIComponent.init()
	--compass = Compass.init()
	--hudRoot.addComponent(compass)
	--hudRoot.addComponent(hudGLUI)
	
	--Define Profile
	local profileFile = io.open(profile, "r")
	if profileFile ~= nil then
		local courseNum = 0
		--read best scores into holes
		while true do
			line = profileFile.read(profileFile)
			if not line then break end
			--course.setBestScore(courseNum, int(line))
			courseNum = courseNum + 1
			print ("Course:" .. courseNum .. " Score:" .. line)
		end
	else
		print("(Lua)Failed to open profile:" .. profile)
	end

	--root.addComponent(course)
	--root.addComponent(hudRoot)
	--root.branch = course
	--root.shouldUpdate = function (comp) return (comp == root.branch) end
	--root.shouldDraw = function (comp) return (comp == root.branch) end
end

function onExit()
	--save best scores from each hole into profile
end

function setInitialCameraPos( num )
	registryTable["camera"]:changeEyePos( eyePosX, eyePosY, eyePosZ )
	registryTable["camera"]:changeLookAtPos( lookAtX, lookAtY, lookAtZ )
	registryTable["camera"]:changeLightPos( lightPosX, lightPosY,lightPosZ )
end

function updateCompass( dT )
	normDir = normalize( camDirX, camDirY, camDirZ )
	dDotNorth = dot( normDir.x, normDir.y, normDir.z, 0, 0, -1 )
	theta = acos( dDotNorth)
	orientation = theta * rad_to_deg
	if normDir.x < 0 then
		orientation = -orientation
	end
	--rotate the compass
	registryTable["compassMesh"]:rotate( orientation, 0, 0, 1 )
end

function updateCamera( dT ) 
    pos = vec3(registryTable["ballKineMatics"]:getPos())
	dir = vec3(registryTable["ballKineMatics"]:getVel())
	normDir = normalize( dir.x, dir.y, dir.z )
	scaleDir = vec3( 0, 0, -0.25 )
	if length( normDir.x, normDir.y, normDir.z ) > 0 then
		scaleDir = vec3( normDir.x * 0.25, normDir.y * 0.25, normDir.z * 0.25 )
	end
	if camProfile == 0 then
		eyePosX = pos.x-scaleDir.x
		eyePosY = pos.y + 0.2
		eyePosZ = pos.z - scaleDir.z
		lookAtX = pos.x
		lookAtY = pos.y+0.1
		lookAtZ = pos.z
		camDirX = lookAtX - eyePosX
		camDirY = lookAtY - eyePosY
		camDirZ = lookAtZ - eyePosZ
		registryTable["camera"]:changeUpDir( 0, 1, 0 )
	elseif camProfile == 1 then
		eyePosX = pos.x
		eyePosY = pos.y + 0.1
		eyePosZ = pos.z
		lookAtX = pos.x+scaleDir.x
		lookAtY = pos.y+0.01
		lookAtZ = pos.z+scaleDir.z
		camDirX = lookAtX - eyePosX
		camDirY = lookAtY - eyePosY
		camDirZ = lookAtZ - eyePosZ
		registryTable["camera"]:changeUpDir( 0, 1, 0 )
	elseif camProfile == 2 then
		eyePosX = pos.x
		eyePosY = pos.y + 6
		eyePosZ = pos.z
		lookAtX = pos.x
		lookAtY = pos.y
		lookAtZ = pos.z
		camDirX = 0
		camDirY = 0
		camDirZ = -1
		registryTable["camera"]:changeUpDir( 0, 0, -1  )
	else
	
	end	
	registryTable["camera"]:changeEyePos( eyePosX, eyePosY, eyePosZ)
	registryTable["camera"]:changeLookAtPos(lookAtX, lookAtY, lookAtZ)
end

function updateBall( dT )
    cupPosX = registryTable["cupPosX"]
    cupPosZ = registryTable["cupPosZ"]
	radius = cupRadius * cupRadius
	ballPos = vec3(registryTable["ballKineMatics"]:getPos())
	diff = vec3( cupPosX - ballPos.x, 0, cupPosZ - ballPos.z )
	mag = (diff.x * diff.x) + (diff.z * diff.z) 
	if radius > mag then
		switchLevel = true
	end	
end

function updateGame( ) 
	if switchLevel == true then
		registryTable["Game"]:switchLevel()
	end
	switchLevel = false
end
		
