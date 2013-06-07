class 'GolfHoleSelector' (Component)

function GolfHoleSelector:__init( filename , start)
	super(self)
	self.holes = { }
	self.setCurrentHole(start)
end

function GolfHoleSelector:update( dT )
	self.holes[self.currentHole].update(dT)
end

function GolfHoleSelector:draw( batch )
	self.holes[self.currentHole].draw( batch )
end

function GolfHoleSelector:getCurrentHole()
	return self.holes[self.currentHole]
end

function GolfHoleSelector:setCurrentHole( hole )
	self.currentHole = hole
end

a = lua_testclass('example')
a:print()