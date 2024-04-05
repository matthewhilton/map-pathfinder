extends Node

@export var test_image: Image

func _ready() -> void:
	print("Hello GDScript!")
	MySingleton.hello_singleton()
	
	var map = BitMap.new()
	map.create(Vector2i(1024,1024))
	map.create_from_image_alpha(test_image)
	map.convert_to_image().save_png("res://bitmap.png")
	var results = MapUtils.process_map(map)
	
	for arr in results:
		var line = Line2D.new()
		
		for vector in arr:
			line.add_point(vector)
		
		add_child(line)
	
	var astar = MapUtils.convert_to_astar(results)
	print(astar)
