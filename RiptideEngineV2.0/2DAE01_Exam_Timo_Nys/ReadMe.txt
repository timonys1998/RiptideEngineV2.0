Riptide engine design choices - https://github.com/timonys1998/RiptideEngine

Engine is inspired by the Unity Entity Component System
Every object in the game consists of different smaller components that all have their own role.

Current components:
TextureComponent: Loads a texture
RenderComponent: Takes a texture and renders that on the screen
Transform: Default made for every gameobject, used to position things on screen
Basecomponent: Basically an interface for all other Components, cannot be instantiated as it is abstract.
InputComponent: Maps keyboard and controllerkeys to commands. Used to control everything in the game.
TextComponent: Close related to texturecomponent but instead makes a text texture instead of an actual image, also used tio change this text.
FPSCalculatorComponent: Calculates the FPS depending on the elapsed time between two frames(deltaTime);
AIComponent: Random movement behaviour.

With this system it is really easy and straightforward to add new components without breaking anything.

Every GameObject can use the templated functions GetComponent to use functionality of the components on the gameobject.

Design choices:
The engine uses no physics or networking so for the gameloop I decided to use a variable time value(deltaTime) instead of a fixed one.
This time is used to make the engine framerate independant.

In the update methods we pass this time, to update specific gameobjects and components framerate independant.

For input I use the command pattern , which basically invokes a certain command objects Execute function on a certain keypress defined by the 
inputcomponent.

My scenegraph makes sure only the scene currently set active is Updated and Rendered -> this to improve performance.

Future changes: More error handling, Scaling of textures, rotation 


