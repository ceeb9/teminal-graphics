# terminal graphics

this is just a simple project for me to learn c++, don't expect too much :)  

## initialization

- Scene(s) are created
- SceneManager is created
- Scenes are added to the SceneManager
- The first active scene is selected
- The main loop starts

## main loop

a few things happen each frame:

### sprite and scene logic

- a ProgramStateInfo object is created and passed to the active scene's OnFrame method
- in the scene's OnFrame method, scene logic happens
- UpdateSprites is called on the active scene, which calls all the sprites in the scene's OnFrame methods

### rendering

- RasterizeSprites is called on the active scene, which calls all the sprites in the scene's Rasterize method
- Each sprite's pixels are ordered by its z-index
- post-processing will happen here (todo)
- final list of pixels is added to the pixel buffer on the renderer
- the pixel buffer of color objects is converted to one string to print on the renderer
- that string is printed to the screen
- the singleton debug box's contents are printed, if enabled

