class 'MyGame' (Game)

function MyGame:__init()
	Game.__init(self)

	s = MyScene()
	self:SetScene(s)
	self.scene = s
	self.game = self

	sprite5 = Sprite("brick.jpg", 50, 150, 10, 0)
	sprite6 = Sprite("brick.jpg", 595, 150, 10, 0)

	-- sprite5.scale = 2.0

	o5 = StaticObject(sprite5)
	o5:CreateBox()
	s:AddChild(o5)
	o6 = StaticObject(sprite6)
	o6:CreateBox()
	s:AddChild(o6)

	sprite = Sprite("icon.jpg", 100, 300, 0, 0)
	o = DynamicObject(sprite)
	o:CreateBox()
	s:AddChild(o)

	s.o = o

	max = 16
	for i = 1, max do
		c = Sprite("wood.jpg", 85 + i * 30.01, 150, 0, 0)
		obj = DynamicObject(c)
		obj:CreateBox()

		if i == 1 then
			j = Joint(o5, obj)
			j:Revolute(50, 150)
		else
			j = Joint(prev, obj)	
			j:Revolute(85 + i * 30.01 - 15, 155)
		end

		if i == max then
			j = Joint(o6, obj)
			j:Revolute(660, 150)
		end

		prev = obj
		s:AddChild(obj)
	end

	x = Sprite("icon.jpg", math.random(800), math.random(600), 10, 0)
	s:AddChild(x)
	-- stress test
	for i = 1, 10000 do
		x = Sprite("icon.jpg", math.random(800), math.random(600), 0, 0)
		s:AddChild(x)
	end

end

function MyGame:Step()
	-- self.sprite:Rotate(1)
end

class 'MyScene' (Scene)

function MyScene:__init()
	Scene.__init(self)
	self.a = {}
	self.i = 0
end

function MyScene:MouseInput(x, y, button_code)
	if button_code == Mouse.left then
		local s = Sprite("circle.png", x, y, 0, 0)
		o = DynamicObject(s)
		o:CreateCircle()
		-- o:CreateCustomShape("object2.json")
		self:AddChild(o)
		self.a[self.i] = o
		self.i = self.i + 1
	elseif button_code == Mouse.right then
		self.i = self.i - 1
		o = self.a[self.i]
		if o then 
			self:DeleteChild(o)
		end
		self.a[self.i] = nil
	end
end

function MyScene:KeyboardInput(key_code)
	if key_code == Key.up then -- "jump"
		impulse = -1000 * self.o.mass;
		o = self.o
		o:ApplyLinearImpulseTocenter(0, impulse)
	end

	-- if key_code == Key.down then
	-- 	self.c:ApplyTorque(5)
	-- end

	-- if key_code == Key.left then
	-- 	self.c:ApplyLinearImpulse(3, 6, 0, 0)
	-- end

	-- if key_code == Key.right then
	-- 	self.c:ApplyAngularImpulse(0.3)
	-- end
end

g = MyGame()
g:Loop()
