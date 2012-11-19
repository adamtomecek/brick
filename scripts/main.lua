class 'MyGame' (Game)

function MyGame:__init()
	Game.__init(self)
end

g = MyGame()

s = Scene()

sprite = Sprite("circle.png", 100, 100, 0)
o = BoxObject(sprite)
s:AddChild(o)


g:SetScene(s)
g:Loop()
