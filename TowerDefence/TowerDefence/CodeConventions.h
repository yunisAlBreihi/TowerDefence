//#includes goes as <> first and then ""
#include <string>
#include <vector>
#include <SDL.h>
#include "IRenderable.h"
#include "GameManager.h"

//Class names are in pascal case
class CodeConventions : public IRenderable
{
	//The private, protected and public is as following:
	//Variables goes first
	//Variables are in camelCase
	private:
		//Pointers to managers go first
		GameManager* gameManager;
		SpriteManager* spriteManager;

		//Then SDL objects
		SDL_Renderer* renderer;
		SDL_Rect rect;

		//And then everything else
		std::vector<int> objects;
		float speed = 0;

	//The order of variables are the same in all categories
	protected:
	public:
	//Never use public variables if not explicity needed. use get and set functions instead

	//Functions goes in the same order, but are always under the variables
	//Functions are in PascalCase
	private:
	protected:
	public:
		//Constructors and Destructors go first, in that order
		CodeConventions();
		~CodeConventions();

		//Then GameLoop Functions
		void Start() override;
		void Update(float deltaTime) override;
		void Render() override;

		//Then regular Functions
		void CreateFun();
		void UseItem(int value);

		//Set and Get functions goes next.
		//Setters go first.
		//start the name with the word Set
		void SetObjects(std::vector<int> vector);
		void SetSpeed(float speed);
		//start the name with the word Get
		//Getters can be declared in the header file
		std::vector<int> GetObjects() { return objects; }
		float GetSpeed() { return speed; }

		//If you have template functions, they go here
		//They also go in the header file, since they won't work in the cpp
		template<typename T>
		T* GetManager(ManagerName managerName);

		//And then you have operator overloading
		const CodeConventions operator=(const CodeConventions other) {};
};

//Interfaces should have an I for clarity
//Create them as classes. same order inside a regular class
class IAttributes {};