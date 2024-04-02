extends Node

func _ready() -> void:
	print("Hello GDScript!")
	$MyNode.hello_node()
	MySingleton.hello_singleton()
	
	var map = BitMap.new()
	map.create(Vector2i(1024,1024))
	MapUtils.process_map(map)
