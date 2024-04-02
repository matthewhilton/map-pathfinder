extends Node

@export var test_image: Image

func _ready() -> void:
	print("Hello GDScript!")
	$MyNode.hello_node()
	MySingleton.hello_singleton()
	
	var map = BitMap.new()
	map.create(Vector2i(1024,1024))
	map.create_from_image_alpha(test_image)
	map.convert_to_image().save_png("res://bitmap.png")
	MapUtils.process_map(map)
