dofile( "GolfAttributes.lua" )

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