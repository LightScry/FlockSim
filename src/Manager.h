class Manager {
	static int CurrentAlignment;
	static int CurrentSeperation;
	static int CurrentCohesion;
	public:
	 	static void gameLoop();
	 	static void update();
};

/*
Manager
	- Holds all global info
		- Current Params
		- Goal (or goals)
	+ Init Simulation
		- Instantiate objects
	+ Run Simulation
		- Begin game loop
	+ Update
		- Change params → Either restart or refresh all states
*/