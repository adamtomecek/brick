class 'MyGame' (Game)

function MyGame:__init()
	Game.__init(self)

	s = MyScene()

	sprite = Sprite("circle.png", 100, 100, 0)
	-- o = CircleObject(sprite)

	self:SetScene(s)
	s:AddChild(sprite)

	self.sprite = sprite
end

function MyGame:Step()
	self.sprite:Rotate(1)
end

class 'MyScene' (Scene)

function MyScene:__init()
	Scene.__init(self)
end

function MyScene:KeyboardInput(key_code)
	print(key_code)
end

function MyScene:MouseInput(x, y, button_code)
	if button_code == Mouse.left then
		local s = Sprite("circle.png", x, y, 0)
		o = CircleObject(s)
	elseif button_code == Mouse.right then
		local s = Sprite("icon.jpg", x, y, 0)
		o = BoxObject(s)
	end

	if o then
		self:AddChild(o)
	end
end

g = MyGame()
g:Loop()
