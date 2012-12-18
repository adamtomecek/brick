class 'MyGame' (Game)

function MyGame:__init()
	Game.__init(self)

	s = MyScene()

	sprite = Sprite("circle.png", 100, 100, 10, 0)
	-- o = CircleObject(sprite)

	self:SetScene(s)
	o = CircleObject(sprite)

	s:AddChild(o)

	self.sprite = o
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

function MyScene:KeyboardInput(key_code)
	print(key_code)
end

function MyScene:MouseInput(x, y, button_code)
	if button_code == Mouse.left then
		local s = Sprite("circle.png", x, y, 0, 0)
		o = CircleObject(s)
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

g = MyGame()
g:Loop()
