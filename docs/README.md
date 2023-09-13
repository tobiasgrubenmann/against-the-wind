# Against the Wind (Unreal Demo)

## About

This project was created to demonstrate wind physics using the Unreal Engine 5. It has been tested with Unreal Engine 5.3.0.

The driving physics for the vehicle and cloth physics for the flag are using the built-in Chaos Physics engine of Unreal Engine. The Aerodynamic forces acting on the vehcile and the calculation of the wind shadow are custom code.

The code for the aerodynamic forces is split into two modules, `WindPhysics` for the physics simulation, and `WindPhysicsTest` for the unit tests of the former module.

The wind simulation has the following features:
- Objects create a wind shadow which fades with the distance from the object that causes the wind shadow. This fading distance and hence, the influence of the wind shadow can be set for each actor individually.
- An object that is influenced by aerodynamic forces (e.g., the truck in the demo) has 12 different points of attack. Only those points that are exposed to the wind are experiencing a force. This can cause an object to rotate, as seen at the end of the demo video.
- The force acting on an object depends on the cross-sectional area that is exposed to the wind, the density of the air, the speed and direction of the wind, and the aerodynamic constant of the affected object.
- A special component allows built-in wind simulations (e.g. the cloth simulation) to interact with the wind and take into account the wind-shadow.

## Demo video

A demo video can be found [here](https://gru.ddnss.org/f/2eb226ea9474458ab6e1/).