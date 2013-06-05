
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
		end
	end
	print ("Filename:" .. filename)
	print ("Hole:" .. hole)

	--require(GolfHoleSelector)
	--course = GolfHoleSelector.__init(filename)
	--course.setCurrentHole(hole)
	
	--Define HUD
	--hudRoot = GolfHud.init()
	--hudGLUI = GLUIComponent.init()
	--compass = Compass.init()
	--hudRoot.addComponent(compass)
	--hudRoot.addComponent(hudGLUI)
	
	--root.addComponent(course)
	--root.addComponent(hudRoot)
	--root.branch = course
	--root.shouldUpdate = function (comp) return (comp == root.branch) end
	--root.shouldDraw = function (comp) return (comp == root.branch) end
end

function setInitialCameraPos( )
	registryTable["camera"]:changeEyePos( eyePosX, eyePosY, eyePosZ )
	registryTable["camera"]:changeLookAtPos( lookAtX, lookAtY, lookAtZ )
	registryTable["camera"]:changeLightPos( lightPosX, lightPosY,lightPosZ )
end

require( "GolfAttributes" )