require 'math'

MyGame = {}

MyGame.new = function()
	local self = {}
	-- sprite = Sprite("icon.jpg", 300, 300, 0)
	-- sprite2 = Sprite("icon.jpg", 100, 100, 0)

	-- b1 = BoxObject(sprite)
	-- b2 = BoxObject(sprite2)

	-- sprite3 = Sprite("circle.png", 200, 100, 0)
	-- sprite4 = Sprite("circle.png", 300, 100, 0)

	-- b3 = CircleObject(sprite3)
	-- b4 = CircleObject(sprite4)

	n = Node()
	-- n:AddChild(b1)
	-- n:AddChild(b2)
	-- n:AddChild(b3)
	-- n:AddChild(b4)

	s1 = Sprite("icon.jpg", 200, 200, 0)
	-- s2 = Sprite("icon.jpg", 300, 300, 0)
	-- s3 = Sprite("icon.jpg", 400, 400, 0)

	-- s1:AddChild(s2)
	-- s2:AddChild(s3)
	
	n:AddChild(s1)
	self.n = n
	-- self.create_box()
	self.s1 = s1
	--
	
	for i = 0, 10, 1 do 
		x = math.random(700)
		y = math.random(500)
		x = math.random(20,200)
		s = Sprite("circle.png", x, y, 0)
		c = Chunk()
		self.n:AddChild(Sprite("test.png", x, y, 0))
		o = CircleObject(s)
		self.n:AddChild(o)
	end

	-- for i = 0, 100, 1 do 
	-- 	x = math.random(700)
	-- 	y = math.random(500)
	-- 	r = math.random(20,200)
	-- 	s = Sprite("circle.png", x, y, 0)
	-- 	o = CircleObject(s)
	-- 	self.n:AddChild(o)
	-- end

	self.handle_input = function(key_code)
		-- print(key_code)
		self.create_box()
	end

	self.create_box = function()
		x = math.random(700)
		y = math.random(500)
		r = math.random(20,200)
		s = Sprite("circle.png", x, y, 0)
		o = CircleObject(s)
		self.n.AddChild(o)
	end

	self.loop = function()
		self.s1:Rotate(1)
		self.n:Render()
	end

	return self
end

