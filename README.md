# MapUtils

A very tiny GDExtension addon for Godot that allows you to [skeletonise](https://en.wikipedia.org/wiki/Morphological_skeleton) bitmaps. I.e. given an image, find the 'centers' of the paths.

This can be used, for example, to find the centers of player-built paths.

This uses a skeletonisation script by LingDong, available here: https://github.com/LingDong-/skeleton-tracing

## Using in Godot
1. Go to the `actions` tab in github
2. Click the latest passing workflow run
3. Scroll down to `artifacts` and download `map-pathfinder`
4. In the zip there is an addons folder. Copy the file `map-pathfinder` into your Godot projects `addons` directory

## Useful functions

### `process_map`
Given a bitmap, converts it into polylines (Array of Vector2is that connect to each other)

### `convert_to_astar`
Converts polylines (usually generated from above function) into an [AStar2D](https://en.wikipedia.org/wiki/A*_search_algorithm) graph