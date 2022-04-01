#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"

#include "Plane.h"
#include "Cube.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Grid.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtx/string_cast.hpp>

#include "PhysicsEngine.h"
#include "ScenePhyCollision.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "Input.h"

class SceneData
{
public:
	Texture* floorTexture;
	Texture* cubeTexture;
	//Texture* GoalTexture;
	Texture* ball;


	Shader* floorShader;
	Shader* cubeShader;
	Shader* cubeShader2;
	Shader* cubeShader3;


	DirectionalLight* dlight;

	SpotLight* slight;

	
	Material* cubeMaterial_0;
	Material* cubeMaterial_1;
	Material* cubeMaterial_2;
	



	Cube* cube[200];
	Grid* grid;

	string fname;

	vector<vector<string>> content;
	vector<string> row;
	string line, word;



	int cubeNum = 0;
	int cubeMax = 0;
	int x = 0;
	int y = 0;
	int z = 0;

	float cubePlacementX[500];
	float cubePlacementY[500];
	float cubePlacementZ[500];
	float cubeScale[500];
	
	float XNormalizeFrom;
	float YNormalizeFrom;
	float ZNormalizeFrom;
	float ScaleNormalizeFrom;
	
	float NormalizeStrength_1;
	float NormalizeStrength_2;
	float NormalizeStrength_3;

	PhysicsEngine* phyEng;

	Input* input;

	Camera* camera;

	SceneData(int SCR_WIDTH, int SCR_HEIGHT, PhysicsEngine* physicsEngine, Input* _input);
	int ReadFile();
	void NormalizeData();
	void Update(float deltaTime);

	void Render();

};