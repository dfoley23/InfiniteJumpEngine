
rad_to_deg = 57.2957795131

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
	--course = GolfHoleSelector.__init(filename, hole)
	
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

function setInitialCameraPos( num )
	registryTable["camera"]:changeEyePos( eyePosX, eyePosY, eyePosZ )
	registryTable["camera"]:changeLookAtPos( lookAtX, lookAtY, lookAtZ )
	registryTable["camera"]:changeLightPos( lightPosX, lightPosY,lightPosZ )
end

function updateCompass( dT )
	dir = vec3(registryTable["camera"]:getDir())
	dir.y = 0
	normDir = normalize( dir.x, dir.y, dir.z )
	dDotNorth = dot( normDir.x, normDir.y, normDir.z, 0, 0, -1 )
	theta = acos( dDotNorth)
	orientation = theta * rad_to_deg
	if normDir.x < 0 then
		orientation = -orientation
	end
	--rotate the compass
	registryTable["compassMesh"]:rotate( orientation, 0, 0, 1 )
end

require( "GolfAttributes" )
require( "MiniGolfInput" )