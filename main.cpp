#include <tigl.h>
//This comment is here so that tigl stays at the top even on code reformatting. tigl needs to load first then glfw otherwise glad gets included twice
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "FileReaderFactory.h"
#include "GameTimer.h"
#include "Scene.h"
#include "SceneLoader.h"
#include "components/Camera.h"
#include "components/Mesh.h"
#include "components/Transform.h"
#include "components/scripts/TankScript.h"

/*!@mainpage 3D graphics and C++ EindOpdracht
 *
 * @section wat heb ik gemaakt
 *
 * ik heb ecs (entity component system) gemaakt.
 * hierbij heb ik overal smart pointers gebruikt.
 * ik heb een voorbeeld gemaakt van wat er gemaakt zou kunnen worden met dit ecs.
 * ook heb ik een manier gemaakt om scene's in te laden vanuit een text of json bestand
 * @section GamePlay
 * De applicatie duurt lang om te starten ongeveer 60 sec, je kan dit verminderen door in de main LoadGround() uit te zetten, dan is er geen omgeving meer, maar gaat wel een stuk sneller
 * De gameplay is je bent een tank die kan rondrijden en kan schieten
 * @subsection Controls
 * W: is vooruit
 * S: is achteruit
 * A: is naar links draaien
 * D: is naar rechts draaien
 * Space: is schieten
 * @section installatie instructies
 * er is gebruik gemaakt van de MinGW toolset en de Ninja Build Tool in Combinatie met Cmake
 * de makkelijkste manier om te builden is om gebruik te maken van clion hier is namelijk een bijpassende configuratie meegeleverd
 * @subsection MinGW
 * Ga naar Settings >> Build, Execution, Deployment >> Toolchains
 *	klik hier op de plus en kies MinGW
 * Er zou dan Toolset Bundled MinGw moeten staan, staat dit er niet klik dan op de download knop die rechts staat.
 * kies als cmake Bundled
 * kies als build tool: ninja
 * kies als C Compiler gcc.exe
 * kies als C++ g++.exe
 * kies als Debugger Bundled GDB
 * klik op oke en daarna de groene pijl in clion
 * @subsection PowerShell and Default Environment
 * open powershell in directory of this project
 * run: cmake -Bbuild
 * run daarna: cmake --build build/
 * dit genereerd een .exe in de folder ./build
 * @subsection running tests
 * Test worden gedaan doormiddel van Catch2 V3.0 deze versie is niet meer 1 .h file, maar een globale installatie.
 * heeft u Catch2 nog niet globaal geinstalleerd doe dit dan als volgt:
 * Open powershell als administrator
 * ga naar een folder zolang deze maar niet onderdeel is van dit project
 * voor niet MSCV installatie doe het volgende:
 * @code $ git clone https://github.com/catchorg/Catch2.git
 * cd Catch2
 * cmake -Bbuild
 * cmake --build build/ --target install @endcode
 * voor MSCV doe het volgende
 * @code git clone https://github.com/Microsoft/vcpkg.git
 * cd vcpkg
 * ./bootstrap-vcpkg.sh
 * ./vcpkg integrate install
 * ./vcpkg install catch2 @endcode
 * <div markdown="1">
 * Requirements C++  | Locatie of Methode van voldoening
 * ------------- | -------------
 * De code gebruikt een consistente en gedocumenteerde stijl in layout en naamgeving.  | ik heb clangFormat gebruikt, de uitleg van de code style staat in .clang-format
 * De code gebruikt geen overbodige #defines en bevat geen magische constanten.  | Elke define heeft zijn betekenis erbij staan, erzijn geen overbodige defines
 * De code bevat geen leaks van memory of andere resources | er wordt gebruik gemaakt van smart pointers en elk model wordt na het laden verwijderd
 * De code gebruikt op ten minste 1 plek op een zinnige wijze overerving en virtuele functie(s). | Component is een klasse met overscrhijfbare functies die door specifieke components kunnen worden overschreven
 * Dit wordt aangetoond met een UML-diagram van de betreffende klassen | @see Component
 * De code bevat een herbruikbaar onderdeel, dat gedocumenteerd is met Doxygen en getest met Catch2 of een andere vorm van geautomatiseerde unit-test | InputSystem is een herbruikbaar onderdeel, De testen staan in test.cpp
 * De code gebruikt waar dit mogelijk en zinnig is STL containers en algoritmen | de GameOjects worden verwijderd als ze zelf aangeven dat ze verwijderd willen woorden hierbij word gebruik gemaakt van het erase(remove_if) algoritme
 * De applicatie leest gegevens in vanuit een tekst file naar in-memory data, volgens het factory pattern. | heb hier in de Scene_Loader gebruik gemaakt van factory pattern die kan switchen tussen json en txt files uitlezen om objecten in te laden @see FileReaderFactory
 * De code gebruikt waar mogelijk en zinnig const, constexpr en override | overal waar het kon heb ik gebruik gemaakt van const zichtbaar in bv Transform
 * De code gebruikt consistent smart pointers en andere vormen van RAII | zie Scene en GameOject
 * Het inlezen van de gegevens geeft bij een fout in de gegevens een zinnige foutmelding, waarbij gebruik wordt gemaakt van exceptions | hier is niet opgelet bij het inlezen van txt, bij het inlezen van json worden de exeptions van de library gebruikt
 * De code maakt gebruik van data-driven programming | ja? zie SceneLoader
 * De code maakt gebruik van lambda’s | ja je kan een labmda meegeven aan InputSystem#AddKeyFunction zie TankScript voor een implentatie hiervan
 * De code maakt gebruik van exception handling | in de main worden Exeption gegooid wanneer glfw zichzelf niet kan initializeren
 * De code gebruikt een zelfgeschreven STL-stijl container of algorithme | denk het niet of Templated toevoegen aan een Vector moet tellen
 * De code voldoet aantoonbaar aan andere, wenselijke (kwaliteit verhogende) en gespecificeerde criteria. | Ik heb Templates gebruikt op meerdere plekken, deze templates zijn ook type Veilig zie bv GameObject#AddComponent @see GameObject
 * </div>
 *
 */
void Init();

void Update();

void Draw();

void WorldInit();

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

int main()
{
	GLFWwindow* window;

	if (!glfwInit())
		throw std::runtime_error("Could not initialize GLFW");

	int count;
	glfwGetMonitors(&count);

	window = glfwCreateWindow(1280, 720, "hello world", nullptr, nullptr);
	if (count > 1)
	{
		glfwSetWindowMonitor(window, nullptr, 500, -800, 1280, 720, 240);
	}
	else
	{
		glfwSetWindowMonitor(window, nullptr, 0, 0, 1280, 720, 240);
	}
	// get resolution of monitor
	glfwSwapInterval(1);
	if (!window)
	{
		glfwTerminate();
		throw std::runtime_error("Could not initialize GLFW");
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	tigl::init();
	Init();
	WorldInit();

	glfwSetKeyCallback(window, KeyCallback);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	while (!glfwWindowShouldClose(window))
	{
		Update();
		Draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void Init()
{
	int value[10];
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, value);
}

std::shared_ptr<Scene> scene;

void GeneratePlayerTank()
{
	auto tankGameObject = std::make_shared<GameObject>();
	auto transform = tankGameObject->AddComponent<Transform>(glm::vec3(0, 0, 0),
	                                                         glm::radians(glm::vec3(0.0f, 12.0f, 0.0f)),
	                                                         glm::vec3(1.0f, 1.0f, 1.0f));
	tankGameObject->AddComponent<Mesh>(transform, "../resource/models/tanks/tank2.obj");
	tankGameObject->AddComponent<Camera>(scene, transform);
	tankGameObject->AddComponent<TankScript>(scene, transform);
	scene->AddGameObject(tankGameObject);
}

void LoadGround()
{
	auto groundObject = std::make_shared<GameObject>();
	auto transform = groundObject->AddComponent<Transform>(glm::vec3(0, -1.0f, 0));
	groundObject->AddComponent<Mesh>(transform, "../resource/models/ground/ground.obj");
	scene->AddGameObject(groundObject);
}

void WorldInit()
{
	scene = std::make_shared<Scene>();

	SceneLoader::LoadScene(scene, "../resource/scenes/scene.json");

	GeneratePlayerTank();
	LoadGround();
}

//float rotation = 0.0f;
void Update()
{
	GameTimer::Update(glfwGetTime());
	scene->Update();
}

void Draw()
{
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::mat4 projection = glm::perspective(glm::radians(75.0f), (float)viewport[2] / (float)viewport[3], 0.01f,
	                                        100.0f);

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(scene->GetViewMatrix());
	tigl::shader->enableColor(true);
	tigl::shader->setModelMatrix(glm::mat4(1.0f));
	tigl::shader->enableFog(true);
	tigl::shader->setFogColor(glm::vec3(0.3f, 0.4f, 0.6f));
	tigl::shader->setFogExp2(0.02f);
	tigl::shader->enableLighting(true);
	tigl::shader->setLightCount(1);
	tigl::shader->setLightDirectional(0, true);
	tigl::shader->setLightPosition(0, glm::vec3(1, 2, 3));

	tigl::shader->setLightAmbient(0, glm::vec3(0.1f, 0.1f, 0.15f));
	tigl::shader->setLightDiffuse(0, glm::vec3(0.8f, 0.8f, 0.8f));
	tigl::shader->setLightSpecular(0, glm::vec3(0, 0, 0));
	tigl::shader->setShinyness(32.0f);

	//glBindTexture(GL_TEXTURE_2D, texture);
	//tigl::shader->enableTexture(true);
	glEnable(GL_DEPTH_TEST);
	glPointSize(10.0f);

	scene->Draw();

	//tigl::shader->setModelMatrix(glm::mat4(1.0f));
	//	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	//	tigl::begin(GL_TRIANGLES);
	//
	//	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-10, -1, -10), glm::vec4(1, 1, 1, 1)));
	//	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-10, -1, 10), glm::vec4(1, 1, 1, 1)));
	//	tigl::addVertex(tigl::Vertex::PC(glm::vec3(10, -1, 10), glm::vec4(1, 1, 1, 1)));
	//
	//	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-10, -1, -10), glm::vec4(1, 1, 1, 1)));
	//	tigl::addVertex(tigl::Vertex::PC(glm::vec3(10, -1, -10), glm::vec4(1, 1, 1, 1)));
	//	tigl::addVertex(tigl::Vertex::PC(glm::vec3(10, -1, 10), glm::vec4(1, 1, 1, 1)));
	//
	//	tigl::end();
}

void KeyCallback(GLFWwindow*, int key, int, int action, int)
{
	scene->GetInputSystem().TriggerKeyFunction(key, action);
}

void FramebufferSizeCallback(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
	Draw();
}
