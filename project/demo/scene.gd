extends Node

@export var test_image: Image

func _ready() -> void:
	var results = MapUtils.process_map(test_image)
	
	for arr in results:
		var line = Line2D.new()
		
		for vector in arr:
			line.add_point(vector)
		
		add_child(line)
	
	print(results)
	var astar = MapUtils.convert_to_astar(results)
	
	print("Astar:")
	print(astar)
