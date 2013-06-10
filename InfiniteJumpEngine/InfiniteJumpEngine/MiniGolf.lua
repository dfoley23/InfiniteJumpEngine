
function loadDefaultScene()
	--Define Root
	--root = ComponentContainer.__init()
	
	--Define Camera
	--camera = Camera.__init()
	
	--Define Course
	local hole = 0
	local filename = "Levels/course.db"
	local profile = "Profiles/default.sav"
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
	--require(GolfHoleSelector)
	--course = GolfHoleSelector.__init(filename, hole)
	
	--Define HUD
	--hudRoot = GolfHud.init()
	--hudGLUI = GLUIComponent.init()
	--compass = Compass.init()
	--hudRoot.addComponent(compass)
	--hudRoot.addComponent(hudGLUI)
	
	--Define Profile
	--open file
	--read best scores into holes
	
	--root.addComponent(course)
	--root.addComponent(hudRoot)
	--root.branch = course
	--root.shouldUpdate = function (comp) return (comp == root.branch) end
	--root.shouldDraw = function (comp) return (comp == root.branch) end
end

function onExit()
	--save best scores from each hole into profile
end

function setInitialCameraPos( )
	registryTable["camera"]:changeEyePos( eyePosX, eyePosY, eyePosZ )
	registryTable["camera"]:changeLookAtPos( lookAtX, lookAtY, lookAtZ )
	registryTable["camera"]:changeLightPos( lightPosX, lightPosY,lightPosZ )
end

require( "GolfAttributes" )