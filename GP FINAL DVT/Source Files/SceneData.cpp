#include "SceneData.h"
#include <algorithm>


SceneData::SceneData(int SCR_WIDTH, int SCR_HEIGHT, PhysicsEngine* physicsEngine, Input* _input)
{
	// configure global opengl state
	glEnable(GL_DEPTH_TEST);

	phyEng = physicsEngine;

	input = _input;

	fname = "resources\\data\\SampleCSV.csv";

	floorTexture = new Texture();
	floorTexture->Load("resources\\textures\\FloorTileTexture4.jpg");
	floorTexture->SetSamplerObjectParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	floorTexture->SetSamplerObjectParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	floorTexture->SetSamplerObjectParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	floorTexture->SetSamplerObjectParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);






	camera = new Camera(SCR_WIDTH, SCR_HEIGHT);
	camera->SetPerspectiveProjectionMatrix(glm::radians(100.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 1.0f, 5000.0f);
	glm::vec3 camPos = glm::vec3(-500.0, 300.0, 500.0);
	glm::vec3 camView = glm::vec3(0.0, 10, 0.0);
	glm::vec3 camUp = glm::vec3(0.0, 1.5, 0.0);
	camera->Set(camPos, camView, camUp);

	dlight = new DirectionalLight(glm::vec3(0.0, 0.0, 0.0), glm::vec3(-0.25, -0.5, 0.5));
	dlight->diffuse = glm::vec3(1.0, 1.0, 1.0);
	dlight->ambient = glm::vec3(0.5, 0.5, 0.5);


	cubeShader = new Shader("resources\\shader\\basicTextureLight.vs", "resources\\shader\\basicTextureLight.fs");
	cubeShader2 = new Shader("resources\\shader\\basicTextureLight.vs", "resources\\shader\\basicTextureLight.fs");
	cubeShader3 = new Shader("resources\\shader\\basicTextureLight.vs", "resources\\shader\\basicTextureLight.fs");
	floorShader = new Shader("resources\\shader\\basicTextureLight.vs", "resources\\shader\\basicTextureLight.fs");






	glm::vec4 color1 = glm::vec4(0.0f, 0.5f, 0.75f, 1.0f);
	cubeMaterial_0 = new Material(cubeShader, color1);
	cubeMaterial_0->linkLight(dlight);
	cubeMaterial_0->linkCamera(camera);
	
	glm::vec4 color2 = glm::vec4(0.75f, 0.25f, 0.0f, 1.0f);
	cubeMaterial_1 = new Material(cubeShader2, color2);
	cubeMaterial_1->linkLight(dlight);
	cubeMaterial_1->linkCamera(camera);

	glm::vec4 color3 = glm::vec4(0.75f, 0.0f, 0.0f, 1.0f);
	cubeMaterial_2 = new Material(cubeShader3 , color3);
	cubeMaterial_2->linkLight(dlight);
	cubeMaterial_2->linkCamera(camera);





	//DATA...................

	ReadFile();
	NormalizeData();
	grid = new Grid(camera);




	for (int i = 0; i < cubeMax; i++)
	{
		if(cubePlacementX[i] <= 30)
		    cube[i] = new Cube(cubeMaterial_0, NULL);

		else if (cubePlacementX[i] >= 30 && cubePlacementX[i] <= 60 )
			cube[i] = new Cube(cubeMaterial_1, NULL);
		
		else if (cubePlacementX[i] >= 60)
			cube[i] = new Cube(cubeMaterial_2, NULL);

		cube[i]->transform->translate(glm::vec3(cubePlacementX[cubeNum], cubePlacementY[cubeNum], cubePlacementZ[cubeNum]));
		cube[i]->transform->scale(glm::vec3(1 * cubeScale[cubeNum], 1 * cubeScale[cubeNum], 1 * cubeScale[cubeNum]));
		cubeNum++;
	}


}

int SceneData::ReadFile()
{
	fstream file(fname, ios::in);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			row.clear();

			stringstream str(line);

			while (getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		cout << "Could not open the file\n";

	cout << "\n"; cout << "\n";
	cout << "Data Read: \n";
	cout << "\n"; 

	for (int i = 0; i < content.size(); i++)
	{


		for (int j = 0; j < content[i].size(); j++)
		{
			if (j == 0) {
				cubePlacementX[cubeMax] = std::stof(content[i][j]);
				cout << content[i][j] << " ";
			}
			else if (j == 1) {
				cubePlacementY[cubeMax] = std::stof(content[i][j]);
				cout << content[i][j] << " ";
			}
			else if (j == 2) {
				cubePlacementZ[cubeMax] = std::stof(content[i][j]);
				cout << content[i][j] << " ";
			}
			else if (j == 3) {
				cubeScale[cubeMax] = std::stof(content[i][j]);
				cout << content[i][j] << " ";
			}
			else
				cout << ("Only Float Input Acepted");

		}
		cubeMax++;
		cout << ("\n");
	}
	return 0;
}



//void SceneData::NormalizeData()
//{
//	XNormalizeStrength = 2.0f;
//	YNormalizeStrength = 2.0f;
//	ZNormalizeStrength = 2.0f;
//	ScaleNormalizeStrength = 1.0f;
//
//	cout << "\n"; cout << "\n";
//	cout << "Normalized Data: ";
//	cout << "\n"; cout << "\n";
//	for (int i = 0; i < cubeMax; i++)
//	{
//		
//		cout << cubePlacementX[i];
//		cout << " ";
//		cout << cubePlacementY[i];
//		cout << " ";
//		cout << cubePlacementZ[i];
//		cout << " ";
//		cout << cubeScale[i];
//		cout << "          ";
//
//		//Normalizing X
//
//		int count = 0;
//		int a = cubePlacementX[i];
//		while (a != 0)
//		{
//			a = a / 10;
//			++count;
//		}
//		if (cubePlacementX[i] >= XNormalizeStrength || cubePlacementX[i] < -XNormalizeStrength) {
//			if (count == 2)
//			{
//				cubePlacementX[i] *= 1;
//			}
//			else if (count == 3)
//			{
//				cubePlacementX[i] *= 0.5;
//			}
//			else if (count == 4)
//			{
//				cubePlacementX[i] *= 0.01;
//			}
//			else if( count > 4)
//			{
//				cout << "\n";
//				cout << cubePlacementX[i];
//				cout << " ";
//				cout << "Value data might not be shown on the screen.";
//			}
//		}
//
//		//Normalizing Y
//
//		count = 0;
//		a = cubePlacementY[i];
//		while (a != 0)
//		{
//			a = a / 10;
//			++count;
//		}
//		if (cubePlacementY[i] > YNormalizeStrength || cubePlacementY[i] < -YNormalizeStrength) {
//			if (count == 2)
//			{
//				cubePlacementY[i] *= 0.75;
//			}
//			else if (count == 3)
//			{
//				cubePlacementY[i] *= 0.1;
//			}
//			else if (count == 4)
//			{
//				cubePlacementY[i] *= 0.01;
//			}
//			else if (count > 4)
//			{
//				cout << "\n";
//				cout << cubePlacementY[i];
//				cout << " ";
//				cout << "Value data might not be shown on the screen.";
//			}
//		}
//
//
//		//Normalizing Z
//
//		count = 0;
//		a = cubePlacementZ[i];
//		while (a != 0)
//		{
//			a = a / 10;
//			++count;
//		}
//		if (cubePlacementZ[i] > ZNormalizeStrength || cubePlacementZ[i] < -ZNormalizeStrength) {
//			if (count == 2)
//			{
//				cubePlacementZ[i] *= 0.75;
//			}
//			else if (count == 3)
//			{
//				cubePlacementZ[i] *= 0.1;
//			}
//			else if (count == 4)
//			{
//				cubePlacementZ[i] *= 0.01;
//			}
//			else if (count > 4)
//			{
//				cout << "\n";
//				cout << cubePlacementZ[i];
//				cout << " ";
//				cout << "Value data might not be shown on the screen.";
//			}
//		}
//
//		//Normalizing Scale
//
//		if (cubeScale[i] >= ScaleNormalizeStrength && cubeScale[i] < (ScaleNormalizeStrength + 0.25f)) {
//		
//				cubeScale[i] *= 0.3f;	
//		}
//		else if (cubeScale[i] >= (ScaleNormalizeStrength + 0.25) && cubeScale[i] < (ScaleNormalizeStrength + 0.5f)) {
//
//			cubeScale[i] *= 0.2f;
//		}
//		else if (cubeScale[i] >= (ScaleNormalizeStrength + 0.5)) {
//
//			cubeScale[i] *= 0.1f;
//		}
//		else 
//		{
//			cout << "\n";
//			cout << cubeScale[i];
//			cout << " ";
//			cout << "Value data might not be shown on the screen.";
//		}
//
//		cout << " ";cout << " ";cout << " ";cout << " ";
//		cout << cubePlacementX[i];
//		cout << " ";
//		cout << cubePlacementY[i];
//		cout << " ";
//		cout << cubePlacementZ[i];
//		cout << "\n"; 
//	}
//}
//
void SceneData::NormalizeData()
{
	XNormalizeFrom = 1.0f;
	YNormalizeFrom = 1.0f;
	ZNormalizeFrom = 1.0f;
	ScaleNormalizeFrom = 1.0f;


	NormalizeStrength_1 = 0.5f;
	NormalizeStrength_2 = 0.5f;
	NormalizeStrength_3 = 0.05f;

	cout << "\n"; cout << "\n";
	cout << "Normalized Data: ";
	cout << "\n"; cout << "\n";
	for (int i = 0; i < cubeMax; i++)
	{

		cout << cubePlacementX[i];
		cout << " ";
		cout << cubePlacementY[i];
		cout << " ";
		cout << cubePlacementZ[i];
		cout << " ";
		cout << cubeScale[i];
		cout << "          ";

		//Normalizing X

		int count = 0;
		int a = cubePlacementX[i];
		while (a != 0)
		{
			a = a / 10;
			++count;
		}
		if (cubePlacementX[i] >= XNormalizeFrom || cubePlacementX[i] < -XNormalizeFrom) {
			if (count == 2)
			{
				cubePlacementX[i] *= NormalizeStrength_1;
			}
			else if (count == 3)
			{
				cubePlacementX[i] *= NormalizeStrength_2;
			}
			else if (count == 4)
			{
				cubePlacementX[i] *= NormalizeStrength_3;
			}
			else if (count > 4)
			{
				cout << "\n";
				cout << cubePlacementX[i];
				cout << " ";
				cout << "Value data might not be shown on the screen.";
			}
		}

		//Normalizing Y

		count = 0;
		a = cubePlacementY[i];
		while (a != 0)
		{
			a = a / 10;
			++count;
		}
		if (cubePlacementY[i] > YNormalizeFrom || cubePlacementY[i] < -YNormalizeFrom) {
			if (count == 2)
			{
				cubePlacementY[i] *= NormalizeStrength_1;
			}
			else if (count == 3)
			{
				cubePlacementY[i] *= NormalizeStrength_2;
			}
			else if (count == 4)
			{
				cubePlacementY[i] *= NormalizeStrength_3;
			}
			else if (count > 4)
			{
				cout << "\n";
				cout << cubePlacementY[i];
				cout << " ";
				cout << "Value data might not be shown on the screen.";
			}
		}


		//Normalizing Z

		count = 0;
		a = cubePlacementZ[i];
		while (a != 0)
		{
			a = a / 10;
			++count;
		}
		if (cubePlacementZ[i] > ZNormalizeFrom || cubePlacementZ[i] < -ZNormalizeFrom) {
			if (count == 2)
			{
				cubePlacementZ[i] *= NormalizeStrength_1;
			}
			else if (count == 3)
			{
				cubePlacementZ[i] *= NormalizeStrength_2;
			}
			else if (count == 4)
			{
				cubePlacementZ[i] *= NormalizeStrength_3;
			}
			else if (count > 4)
			{
				cout << "\n";
				cout << cubePlacementZ[i];
				cout << " ";
				cout << "Value data might not be shown on the screen.";
			}
		}

		//Normalizing Scale

		if (cubeScale[i] >= ScaleNormalizeFrom && cubeScale[i] < (ScaleNormalizeFrom + 0.25f)) {

			cubeScale[i] *= 0.3f;
		}
		else if (cubeScale[i] >= (ScaleNormalizeFrom + 0.25) && cubeScale[i] < (ScaleNormalizeFrom + 0.5f)) {

			cubeScale[i] *= 0.2f;
		}
		else if (cubeScale[i] >= (ScaleNormalizeFrom + 0.5)) {

			cubeScale[i] *= 0.1f;
		}
		else
		{
			cout << "\n";
			cout << cubeScale[i];
			cout << " ";
			cout << "Value data might not be shown on the screen.";
		}

		cout << " "; cout << " "; cout << " "; cout << " ";
		cout << cubePlacementX[i];
		cout << " ";
		cout << cubePlacementY[i];
		cout << " ";
		cout << cubePlacementZ[i];
		cout << "\n";
	}
}



void SceneData::Update(float deltaTime)
{
	camera->RotateViewPoint(1500, glfwGetTime()/ 5 );
}

void SceneData::Render()
{
	glClearColor(0.5f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//RENDERING THE DATA OBJECTS..........................
	for (int i = 0; i < cubeMax; i++)
	{
		cube[i]->render();
	}
	grid->Render();

}