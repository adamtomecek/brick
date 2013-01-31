class 'MyGame' (Game)

function MyGame:__init()
	Game.__init(self)

	s = MyScene()

	sprite = Sprite("icon.jpg", 400, 100, 10, 0)
	sprite2 = Sprite("icon.jpg", 0, 0, -20, 0)
	o = BoxObject(sprite)

	self:SetScene(s)
	self.sprite = sprite2
	s:AddChild(sprite2)

	s:AddChild(o)

	s.c = o

	self.scene = s
	self.game = self
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
		o = CustomObject(s, "object2.json")
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

	print(self.i)

	-- if o then
	-- 	self:AddChild(o)
	-- 	self.o = o
	-- end
end

function MyScene:KeyboardInput(key_code)
	if key_code == Key.up then
		jump = true
		self.c:ApplyForceToCenter(0, -2500)
	end

	if key_code == Key.down then
		self.c:ApplyTorque(5)
	end

	if key_code == Key.left then
		self.c:ApplyLinearImpulse(3, 6, 0, 0)
	end

	if key_code == Key.right then
		self.c:ApplyAngularImpulse(0.3)
	end
end

g = MyGame()
g:Loop()
