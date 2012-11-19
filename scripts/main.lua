class 'MyGame' (Game)

function MyGame:__init()
	Game.__init(self)

end

class 'MyScene' (Scene)

function MyScene:__init()
	Scene.__init(self)
end

function MyScene:KeyboardInput(key_code)
	print(key_code)
end

function MyScene:MouseInput(x, y, button_code)
	local s = Sprite("circle.png", x, y, 0)
	local o = CircleObject(s)
	self:AddChild(o)
end

g = MyGame()

s = MyScene()

sprite = Sprite("circle.png", 100, 100, 0)
o = CircleObject(sprite)
s:AddChild(o)


g:SetScene(s)
g:Loop()
