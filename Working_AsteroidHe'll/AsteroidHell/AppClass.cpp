#include "AppClass.h"
using namespace Simplex;
extern float fTimer = 0;
void Application::InitVariables(void)
{
	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Music
	String sRoute = m_pSystem->m_pFolder->GetFolderData();
	sRoute += m_pSystem->m_pFolder->GetFolderAudio();

#pragma region Make some meshes, add them to a group and add the group to a model
	/*
	Mesh* pMesh1 = new Mesh();
	Mesh* pMesh2 = new Mesh();
	Mesh* pMesh3 = new Mesh();
	pMesh1->GenerateCone(1.0f, 1.0f, 10, C_RED);
	pMesh2->GenerateTorus(1.0f, 0.7f, 10, 10, C_MAGENTA);
	pMesh3->GenerateTube(1.0f, 0.7f, 1.0f, 10, C_BLUE);
	int nMesh1 = m_pMngr->AddMesh(pMesh1);
	int nMesh2 = m_pMngr->AddMesh(pMesh2);

	Group* pGroup1 = new Group();
	pGroup1->AddMesh(nMesh1, MeshOptions(glm::translate(AXIS_Y), WIRE));
	pGroup1->AddMesh(nMesh2, MeshOptions(glm::translate(-AXIS_Y), SOLID));
	Group* pGroup2 = new Group();
	pGroup2->AddMesh(pMesh3, MeshOptions(IDENTITY_M4, SOLID | WIRE));

	m_pModel1 = new Simplex::Model();
	m_pModel1->AddGroup(pGroup1);
	m_pModel1->AddGroup(pGroup2);
	*/
#pragma endregion
#pragma region Load Model and change its rendering properties
	/*
	m_pModel1 = new Simplex::Model();
	m_pModel1->Load("Macross\\YF19.BTO");
	m_pModel1->ChangeMeshOptions(MeshOptions(IDENTITY_M4, SOLID | WIRE), -1, -1);
	*/
#pragma endregion
#pragma region Load Model and change its materials
	/*
	m_pModel1 = new Simplex::Model();
	m_pModel1->Load("Macross\\YF19.BTO");
	//m_pModel1->ChangeMeshOptions(MeshOptions(IDENTITY_M4, SOLID | WIRE), -1, -1);
	m_pMatMngr->AddMaterial("Cloud.png", "Cloud.png");
	m_pModel1->ChangeMaterialOfGroup("Cloud.png", "ALL");
	*/
#pragma endregion
#pragma region Load Model disconect and change its materials
	/*
	m_pModel1 = new Simplex::Model();
	m_pModel1->Load("Macross\\YF19.BTO");
	//m_pModel1->ChangeMeshOptions(MeshOptions(IDENTITY_M4, SOLID | WIRE), -1, -1);
	m_pMatMngr->AddMaterial("Cloud.png", "Cloud.png");
	m_pModel1->DuplicateMaterialsUnique(-1, "_copy"); //dupliocate existing materials
	m_pModel1->CreateMaterials(); //duplicate one per mesh
	m_pModel1->ChangeMaterialOfGroup("Cloud.png", "ALL");
	*/
#pragma endregion
#pragma region Load Model and duplicate onto another one
	/*
	m_pModel3 = new Simplex::Model();
	m_pModel3->Load("Macross\\YF19.BTO");
	m_pModel1 = new Simplex::Model();
	m_pModel1->Instance(m_pModel3, "_copy_");
	*/
#pragma endregion
#pragma region Load Model
	/*
	m_pModel1 = new Simplex::Model();
	m_pModel1->Load("Macross\\YF19.BTO");
	*/
#pragma endregion
#pragma region Sandbox
	m_pBackground = new Simplex::Model();
	m_pBackground->Load("Asteroid\\space_background.obj"); //UNCOMMENT THIS TO ADD THE BG BACK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	m_pBackgroundRB = new MyRigidBody(m_pBackground->GetVertexList());
	
	//static int timing = 0;
	timing = 0;

	//for (int i = 0; i < 200; i++) {
	//	Asteroid* temp;
	//	switch (i % 2) {// spawns asteroids on either a veritcal edge or a horizontal edge
	//	case 0:
	//		temp = new Asteroid(vector3(glm::linearRand(-16.5f,16.5f), 1.0f, 11.0f));
	//		break;
	//	case 1:
	//		temp = new Asteroid(vector3(16.5, 1.0f, glm::linearRand(-11.0f, 11.0f)));
	//		break;
	//	default:
	//		temp = new Asteroid(vector3(16.5, 1.0f, glm::linearRand(-11.0f, 11.0f)));
	//	}
	//	
	//	m_AsteroidList.push_back(temp);
	//}

	//Background music
	m_soundBGM.openFromFile(sRoute + "elementary-wave-11.ogg");
	m_soundBGM.play();
	m_soundBGM.setLoop(true);

	//sound effect
	m_soundBuffer.loadFromFile(sRoute + "12C.wav");
	m_sound.setBuffer(m_soundBuffer);

	//MODELING LOADING
	//test = new Simplex::Texture();
	//test->LoadTexture("spaceBox.png");

	m_pShipModel = new Simplex::Model();
	//m_pModel->Load("Lego\\Unikitty.BTO");
	m_pShipModel->Load("Asteroid\\ship.obj");
	m_pModelRB = new MyRigidBody(m_pShipModel->GetVertexList());

	m_pAsteroid = new Simplex::Model();
	//m_pAsteroid->Load("Asteroid\\asteroid.obj");

	m_pShip = new Ship();
	m_pGameOverModel = new Simplex::Model();
	//m_pModel->Load("Lego\\Unikitty.BTO");
	m_pGameOverModel->Load("Asteroid\\gameover.obj");
	m_pGameOverModelRB = new MyRigidBody(m_pGameOverModel->GetVertexList());
#pragma endregion
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();
	
	m_pCameraMngr->SetCameraMode(CAM_ORTHO_Y);
	int height = m_pSystem->GetWindowHeight();//////////we can use these later 
	int width = m_pSystem->GetWindowWidth();
	

	//timer

	static uint uClock = m_pSystem->GenClock();
	fTimer += m_pSystem->GetDeltaTime(uClock);
	//Is the first person camera active?
	CameraRotation();

	if (gameover) {
		
		m_pGameOverModel->SetModelMatrix(glm::translate(vector3(0.0f, 0.0f, 0.0f))*glm::scale(vector3(40.2f)));
		m_pGameOverModelRB->SetModelMatrix(glm::translate(vector3(0.0f, 0.0f, 0.0f))*glm::scale(vector3(40.2f)));
	//	std::cout << m_pGameOverModelRB->GetHalfWidth().length() << std::endl;
		m_pGameOverModel->AddToRenderList();
		m_pGameOverModelRB->AddToRenderList();
	}
	else {

		if (timing%3 == 0 && m_AsteroidList.size() < asteroidNumber/* this number dictates the number of asteroids, change this as needed to tank framerate to test the spacial optimization*/) { 
			for (int i = 0; i < 5; i++) {
				Asteroid* temp;
				switch (i % 2) {// spawns asteroids on either a veritcal edge or a horizontal edge
				case 0:
					temp = new Asteroid(vector3(glm::linearRand(-16.5f, 16.5f), 1.0f, 11.0f));
					break;
				case 1:
					temp = new Asteroid(vector3(16.5, 1.0f, glm::linearRand(-11.0f, 11.0f)));
					break;
				default:
					temp = new Asteroid(vector3(16.5, 1.0f, glm::linearRand(-11.0f, 11.0f)));
				}

				m_AsteroidList.push_back(temp);
			}
		}

		timing++;

		//asteroid update bit
		for each (Asteroid* a in m_AsteroidList)
		{
			a->collisionList.clear();

			//clamp the speed down
			if (a->m_fSpeed > 0.1f) {
				a->m_fSpeed = 0.1f;
			}

			//clamp the y position
			a->m_v3Position.y = 0.0f;
			
			//COLLISION DETECTION HERE
			if (m_bSpacialOptimization) {
				//z: -10 10 x: -17 17
				//x = 0
				//z = 0
				int octant = 8;
				//top row
				if (a->Position().x < -8.5f && a->Position().z < 0.0f) {
					octant = 0;
				}
				else if (a->Position().x >= -8.5f && a->Position().x < 0.0f && a->Position().z < 0.0f) {
					octant = 1;
				}
				else if (a->Position().x >= 0.0f && a->Position().x < 8.5f && a->Position().z < 0.0f) {
					octant = 2;
				}
				else if (a->Position().x >= 8.5f && a->Position().z < 0.0f) {
					octant = 3;
				}
				//bottom row
				else if (a->Position().x < -8.5f && a->Position().z >= 0.0f) {
					octant = 4;
				}
				else if (a->Position().x >= -8.5f && a->Position().x < 0.0f && a->Position().z >= 0.0f) {
					octant = 5;
				}
				else if (a->Position().x >= 0.0f && a->Position().x < 8.5f && a->Position().z >= 0.0f) {
					octant = 6;
				}
				else {
					octant = 7;
				}

				for each(Asteroid * a_Other in m_AsteroidList) {
					switch (octant)
					{
						case 0:
							if (a_Other->Position().x < -8.5f && a_Other->Position().z < 0.0f) {
								a->AsteroidCollision(a_Other);
							}
							break;
						case 1:
							if (a_Other->Position().x >= -8.5f && a_Other->Position().x < 0.0f && a_Other->Position().z < 0.0f) {
								a->AsteroidCollision(a_Other);
							}
							break;
						case 2:
							if (a_Other->Position().x >= 0.0f && a_Other->Position().x < 8.5f && a_Other->Position().z < 0.0f) {
								a->AsteroidCollision(a_Other);
							}
							break;
						case 3:
							if (a_Other->Position().x >= 8.5f && a_Other->Position().z < 0.0f) {
								a->AsteroidCollision(a_Other);
							}
							break;
						case 4:
							if (a_Other->Position().x < -8.5f && a_Other->Position().z >= 0.0f) {
								a->AsteroidCollision(a_Other);
							}
							break;
						case 5:
							if (a_Other->Position().x >= -8.5f && a_Other->Position().x < 0.0f && a_Other->Position().z >= 0.0f) {
								a->AsteroidCollision(a_Other);
							}
							break;
						case 6:
							if (a_Other->Position().x >= 0.0f && a_Other->Position().x < 8.5f && a_Other->Position().z >= 0.0f) {
								a->AsteroidCollision(a_Other);
							}
							break;
						case 7:
							if (a_Other->Position().x >= 8.5f && a_Other->Position().z >= 0.0f) {
								a->AsteroidCollision(a_Other);
							}
							break;
						default:
							std::cout << "IMPOSSIBLE" << std::endl;
							break;
					}
				}
			}
			else {//brute force collision detection
				for each(Asteroid* aOther in m_AsteroidList) {
					a->AsteroidCollision(aOther);
				}
			}
			
			if (!gameover && god == false) { //check for gameover
				gameover = a->ShipCollision(m_pShip);
			}

			a->Update();
		}

		//Ship Update
		m_pShipModel->SetModelMatrix(glm::translate(m_pShip->Position()) * m_pShip->RotationMatrix()*glm::scale(vector3(1.0f)));
		//m_pModelRB->SetModelMatrix(glm::translate(vector3(0.0f))*glm::scale(vector3(5.0f)));

		m_pShip->Update();


		m_pShipModel->AddToRenderList();
		//m_pModelRB->AddToRenderList();

		m_pAsteroid->SetModelMatrix(glm::translate(vector3(10.0f, 1.0f, 0.0f)));
		m_pAsteroid->AddToRenderList();

		m_pBackground->SetModelMatrix(glm::translate(vector3(0.0f, 0.0f, 0.0f))*glm::scale(vector3(3.2f)));
		m_pBackgroundRB->SetModelMatrix(glm::translate(vector3(0.0f, 0.0f, 0.0f))*glm::scale(vector3(3.2f)));

		m_pBackground->AddToRenderList();
		m_pBackgroundRB->AddToRenderList();
	}

	//Move light... just for fun...
	/*
	static double dTimer = 0.0f; //create a variable to store time
	static uint uClock = m_pSystem->GenClock(); //generate a clock to track time
	dTimer += m_pSystem->GetDeltaTime(uClock); //get the time difference since last time called
	double dAngle = MapValue(dTimer, 0.0, 5.0, 0.0, 360.0);//map the value so we do not need to wait 360 seconds, only 5
	
	static vector3 v3Color(C_WHITE); //color of the light
	vector3 v3Position(glm::sin(glm::radians(dAngle)) * 5.0f, 2.5f, glm::cos(glm::radians(dAngle)) * 5.0f);//holds position of light
	m_pLightMngr->SetPosition(v3Position, 1); //set the position of first light(0 is reserved for global light)
	m_pLightMngr->SetIntensity(5.0f, 1); //set the intensity of first light
	m_pLightMngr->SetColor(v3Color, 1); //set the color of first light
	m_pMeshMngr->AddSphereToRenderList(glm::translate(v3Position) * glm::scale(vector3(0.15f)), v3Color, RENDER_SOLID); //add a sphere to "see" it
	*/
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList("Skybox.png"/*"spaceBox.jpg"*//*"Skybox_03.jpg"*//*"spaceBoxSimple.png"*/);
	
	// set the model matrix of the model
	//m_pModel->SetModelMatrix(ToMatrix4(m_qArcBall));
	//play the default sequence of the model

	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();
	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}

void Application::Release(void)
{
	//release GUI
	ShutdownGUI();

	//release variables
	SafeDelete(m_pShipModel);
	SafeDelete(m_pShip);
}