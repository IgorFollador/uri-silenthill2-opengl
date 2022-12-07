#include "Scene6.h"
#include <GL/gl.h>

CScene6::CScene6()
{
	pCamera = NULL;
	pTexto = NULL;
	pTextures = NULL;
	
	bIsWireframe = false;
	bIsCameraFPS = true;

	iFPS = 0;
	iFrames = 0;
	ulLastFPS = 0;
	szTitle[256] = 0;

	isFob = true;

	// Cria gerenciador de impressão de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(0.0f, 100.0f, 100.0f, 3.0f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	fLampPosX = -900.0f;
	fLampPosY = 800.0f;
	fLampPosZ = 700.0f;
	fMoveRate = 3.0f;

	// Carrega todas as texturas
	pTextures = new CTexture();	
	pTextures->CreateTextureClamp(0, "../Scene6/skybox/back.jpg");
	pTextures->CreateTextureClamp(1, "../Scene6/skybox/front.jpg");
	pTextures->CreateTextureClamp(2, "../Scene6/skybox/up.jpg");
	pTextures->CreateTextureClamp(3, "../Scene6/skybox/up.jpg");
	pTextures->CreateTextureClamp(4, "../Scene6/skybox/front.jpg");
	pTextures->CreateTextureClamp(5, "../Scene6/skybox/front.jpg");

	// Carrega o objeto
	pTerreno = NULL;
	pTerreno = new CModel_3DS();
	pTerreno->Load("../Scene6/terreno/terrenoshadow.3DS");

	pFloor = NULL;
	pFloor = new CModel_3DS();
	pFloor->Load("../Scene6/vwfloor.3DS");

	pSideWalk = NULL;
	pSideWalk = new CModel_3DS();
	pSideWalk->Load("../Scene6/sidewalk.3DS");

	pBathroom = NULL;
	pBathroom = new CModel_3DS();
	pBathroom->Load("../Scene6/bathroom.3DS");

	pTrash = NULL;
	pTrash = new CModel_3DS();
	pTrash->Load("../Scene6/trash.3DS");

	pBoxes = NULL;
	pBoxes = new CModel_3DS();
	pBoxes->Load("../Scene6/boxes.3DS");

	pStop = NULL;
	pStop = new CModel_3DS();
	pStop->Load("../Scene6/stop.3DS");

	pPost = NULL;
	pPost = new CModel_3DS();
	pPost->Load("../Scene6/post.3DS");

	pFence = NULL;
	pFence = new CModel_3DS();
	pFence->Load("../Scene6/fence.3DS");

	pCar = NULL;
	pCar = new CModel_3DS();
	pCar->Load("../Scene6/car.3DS");

	isNormalMap = false;
}


CScene6::~CScene6(void)
{
	if (pTexto)
	{
		delete pTexto;
		pTexto = NULL;
	}

	if (pTextures)
	{
		delete pTextures;
		pTextures = NULL;
	}

	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}

	if (pTimer)
	{
		delete pTimer;
		pTimer = NULL;
	}	

	if (pTerreno)
	{
		delete pTerreno;
		pTerreno = NULL;
	}

	if (pFloor)
	{
		delete pFloor;
		pFloor = NULL;
	}

	if (pSideWalk)
	{
		delete pSideWalk;
		pSideWalk = NULL;
	}

	if (pBathroom)
	{
		delete pBathroom;
		pBathroom = NULL;
	}

	if (pTrash)
	{
		delete pTrash;
		pTrash = NULL;
	}

	if (pBoxes)
	{
		delete pBoxes;
		pBoxes = NULL;
	}

	if (pStop)
	{
		delete pStop;
		pStop = NULL;
	}

	if (pPost)
	{
		delete pPost;
		pPost = NULL;
	}

	if (pFence)
	{
		delete pFence;
		pFence = NULL;
	}

	if (pCar)
	{
		delete pCar;
		pCar = NULL;
	}
}




int CScene6::DrawGLScene(void)	// Função que desenha a cena
{
	// Get FPS
	if (GetTickCount() - ulLastFPS >= 1000)	// When A Second Has Passed...
	{
		ulLastFPS = GetTickCount();				// Update Our Time Variable
		iFPS = iFrames;							// Save The FPS
		iFrames = 0;							// Reset The FPS Counter
	}
	iFrames++;									// FPS counter
	
	pTimer->Update();							// Atualiza o timer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpa a tela e o Depth Buffer
	glLoadIdentity();									// Inicializa a Modelview Matrix Atual


	// Seta as posições da câmera
	pCamera->setView();

	// Desenha grid 
	//Draw3DSGrid(20.0f, 20.0f);

	// Desenha os eixos do sistema cartesiano
	DrawAxis();

	// Modo FILL ou WIREFRAME (pressione barra de espaço)	
	if (bIsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (INÍCIO)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	// Desenhar a Lâmpada
	glPushMatrix();
	glTranslatef(fLampPosX, fLampPosY, fLampPosZ);
	glutSolidSphere(7.0, 10, 10);
	glPopMatrix();

	// Configuração da Lâmpada (EMISSOR)
	LightAmbient[0] = 1.0f; LightAmbient[1] = 1.0f; LightAmbient[2] = 1.0f; LightAmbient[3] = 1.0f;
	LightDiffuse[0] = 1.0f; LightDiffuse[1] = 1.0f; LightDiffuse[2] = 1.0f; LightDiffuse[3] = 1.0f;
	LightSpecular[0] = 1.0f; LightSpecular[1] = 1.0f; LightSpecular[2] = 1.0f; LightSpecular[3] = 1.0f;
	LightPosition[0] = fLampPosX; LightPosition[1] = fLampPosY; LightPosition[2] = fLampPosZ; LightPosition[3] = 1.0f;

	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

	MatAmbient[0] = 0.1f; MatAmbient[1] = 0.1f; MatAmbient[2] = 0.1f; MatAmbient[3] = 1.0f;
	MatDiffuse[0] = 1.0f; MatDiffuse[1] = 1.0f; MatDiffuse[2] = 1.0f; MatDiffuse[3] = 1.0f;
	MatSpecular[0] = 0.0f; MatSpecular[1] = 0.0f; MatSpecular[2] = 0.0f; MatSpecular[3] = 1.0f;
	MatShininess = 128.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, MatShininess);

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);	// Habilitar iluminação 
	glEnable(GL_LIGHT0);	// Liga Lampada 0

	glClearColor(0.5f, 0.5f, 0.5f, 1);
	GLfloat fogColor[4] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat density = 0.003f;

	if (isFob) {
		glEnable(GL_FOG);
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogi(GL_FOG_MODE, GL_EXP2);
		glFogf(GL_FOG_DENSITY, density);
	}

	// SkyBox
	CreateSkyBox(0.0f, 1100.0f, 0.0f, 3000.0f, 3000.0f, 3000.0f, pTextures);

	// Terreno
	glPushAttrib(GL_TEXTURE_BIT);
	glPushMatrix();
		glScalef(3.0f, 3.0f, 3.0f);
		glTranslatef(50.0f, -80.0f, 0.0f);
		pTerreno->Draw();
	glPopMatrix();
	glPopAttrib();


	// Chão
	glTranslatef(0.0f, 100.0f, 90.0f);
	glPushAttrib(GL_TEXTURE_BIT);
	glPushMatrix();
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		pFloor->Draw();
	glPopMatrix();
	glPopAttrib();


	// Calçada
	glPushAttrib(GL_TEXTURE_BIT);
	glPushMatrix();
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		pSideWalk->Draw();
	glPopMatrix();
	glPopAttrib();


	// Banheiro
	glPushAttrib(GL_TEXTURE_BIT);
	glPushMatrix();
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		pBathroom->Draw();
	glPopMatrix();
	glPopAttrib();


	// Lixeira
	glPushAttrib(GL_TEXTURE_BIT);
	glPushMatrix();
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		pTrash->Draw();
	glPopMatrix();
	glPopAttrib();


	// Caixas
	glPushAttrib(GL_TEXTURE_BIT);
	glPushMatrix();
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		pBoxes->Draw();
		glPopMatrix();
	glPopAttrib();

	
	// Pare
	glPushAttrib(GL_TEXTURE_BIT);
	glPushMatrix();
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		pStop->Draw();
	glPopMatrix();
	glPopAttrib();


	// Poste
	glPushAttrib(GL_TEXTURE_BIT);
	glPushMatrix();
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		pPost->Draw();
	glPopMatrix();
	glPopAttrib();


	// Cerca
	glPushAttrib(GL_TEXTURE_BIT);
	glPushMatrix();
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		pFence->Draw();
	glPopMatrix();
	glPopAttrib();


	// Car
	glPushAttrib(GL_TEXTURE_BIT);
	glPushMatrix();
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		pCar->Draw();
	glPopMatrix();
	glPopAttrib();

	glDisable(GL_FOG);
	glDisable(GL_LIGHT0);	// Desliga Lampada 0	
	glDisable(GL_LIGHTING);	// Desabilita ilumnação


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
	pTextures->ApplyTexture(7);
	glPushMatrix();
	glTranslatef(0.0f, 180.0f, 0.0f);
	glPopMatrix();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = pTimer->GetTime() / 1000.0f;
	fRenderPosY += 0.002f;

	// Impressão de texto na tela...
	// Muda para modo de projeção ortogonal 2D
	// OBS: Desabilite Texturas e Iluminação antes de entrar nesse modo de projeção
	OrthoMode(0, 0, WIDTH, HEIGHT);


	glPushMatrix();
	glTranslatef(0.0f, HEIGHT - 100, 0.0f);	// Move 1 unidade para dentro da tela (eixo Z)

	// Cor da fonte
	glColor3f(1.0f, 1.0f, 0.0f);


	glRasterPos2f(10.0f, 0.0f);	// Posicionando o texto na tela
	if (!bIsWireframe) {
		pTexto->glPrint("[TAB]  Modo LINE"); // Imprime texto na tela
	}
	else {
		pTexto->glPrint("[TAB]  Modo FILL");
	}


	//// Camera LookAt
	glRasterPos2f(10.0f, 40.0f);
	pTexto->glPrint("Player LookAt  : %f, %f, %f", pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);

	//// Posição do Player
	glRasterPos2f(10.0f, 60.0f);
	pTexto->glPrint("Player Position: %f, %f, %f", pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);

	//// Imprime o FPS da aplicação e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime()/1000));


	glPopMatrix();

	// Muda para modo de projeção perspectiva 3D
	PerspectiveMode();

	return true;
}




void CScene6::MouseMove(void) // Tratamento de movimento do mouse
{
	// Realiza os cálculos de rotação da visão do Player (através das coordenadas
	// X do mouse.
	POINT mousePos;
	int middleX = WIDTH >> 1;
	int middleY = HEIGHT >> 1;

	GetCursorPos(&mousePos);

	if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

	SetCursorPos(middleX, middleY);

	fDeltaX = (float)((middleX - mousePos.x)) / 10;
	fDeltaY = (float)((middleY - mousePos.y)) / 10;

	// Rotaciona apenas a câmera
	pCamera->rotateGlob(-fDeltaX, 0.0f, 1.0f, 0.0f);
	pCamera->rotateLoc(-fDeltaY, 1.0f, 0.0f, 0.0f);
}

void CScene6::KeyPressed(void) // Tratamento de teclas pressionadas
{

	// Verifica se a tecla 'W' foi pressionada e move o Player para frente
	if (GetKeyState('W') & 0x80)
	{
		pCamera->moveGlob(pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);
	}
	// Verifica se a tecla 'S' foi pressionada e move o Player para tras
	else if (GetKeyState('S') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Forward[0], -pCamera->Forward[1], -pCamera->Forward[2]);
	}
	// Verifica se a tecla 'A' foi pressionada e move o Player para esquerda
	else if (GetKeyState('A') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Right[0], -pCamera->Right[1], -pCamera->Right[2]);
	}
	// Verifica se a tecla 'D' foi pressionada e move o Player para direira
	else if (GetKeyState('D') & 0x80)
	{
		pCamera->moveGlob(pCamera->Right[0], pCamera->Right[1], pCamera->Right[2]);
	}
	// Senão, interrompe movimento do Player
	else
	{
	}


	if (GetKeyState(VK_UP) & 0x80)
	{
		fLampPosZ -= fMoveRate;
	}
	if (GetKeyState(VK_DOWN) & 0x80)
	{
		fLampPosZ += fMoveRate;
	}
	if (GetKeyState(VK_LEFT) & 0x80)
	{
		fLampPosX -= fMoveRate;
	}
	if (GetKeyState(VK_RIGHT) & 0x80)
	{
		fLampPosX += fMoveRate;
	}
	if (GetKeyState(VK_PRIOR) & 0x80)
	{
		fLampPosY += fMoveRate;
	}
	if (GetKeyState(VK_NEXT) & 0x80)
	{
		fLampPosY -= fMoveRate;
	}
}

void CScene6::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
{
	switch (wParam)
	{
	case VK_TAB:
		bIsWireframe = !bIsWireframe;
		break;

	case VK_SPACE:
		pTimer->Init();
		break;

	case VK_RETURN:
		isNormalMap = !isNormalMap;
		break;

	case 'F':
		isFob = !isFob;
		break;

	}

}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CScene6::Draw3DSGrid(float width, float length)
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 0.3f, 0.0f);
	glPushMatrix();
	for (float i = -width; i <= length; i += 1)
	{
		for (float j = -width; j <= length; j += 1)
		{
			// inicia o desenho das linhas
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0.0f, j + 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 1, 0.0f, j + 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 1, 0.0f, j);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, 0.0f, j);
			glEnd();
		}
	}
	glPopMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void CScene6::DrawCube(float pX, float pY, float pZ,
	float rX, float rY, float rZ, float angle,
	float sX, float sY, float sZ,
	int texID)
{

	// Seta a textura ativa
	if (texID >= 0)
		pTextures->ApplyTexture(texID);

	glPushMatrix();
	glTranslatef(pX, pY, pZ);
	glRotatef(angle, rX, rY, rZ);
	glScalef(sX, sY, sZ);

	glBegin(GL_QUADS);
	// face frente
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f, 0.5f);

	// face trás
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	
	// face direita
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);

	// face esquerda
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

	// face baixo
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f( 0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);

	// face cima
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f,  0.5f,  -0.5f);

	glEnd();

	glPopMatrix();
}


void CScene6::DrawAxis()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	// Eixo X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);

	// Eixo Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glVertex3f(0.0f, -1000.0f, 0.0f);

	// Eixo Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glEnd();
	glPopMatrix();
}


void CScene6::CreateSkyBox(float x, float y, float z,
	float width, float height, float length,
	CTexture* pTextures)
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPushMatrix();

	// Centraliza o Skybox em torno da posição especificada(x, y, z)
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;


	// Aplica a textura que representa a parte da frente do skybox (BACK map)
	pTextures->ApplyTexture(0);

	// Desenha face BACK do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (FRONT map)
	pTextures->ApplyTexture(1);

	// Desenha face FRONT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (DOWN map)
	pTextures->ApplyTexture(2);

	// Desenha face BOTTOM do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (UP map)
	pTextures->ApplyTexture(3);

	// Desenha face TOP do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (LEFT map)
	pTextures->ApplyTexture(4);

	// Desenha face LEFT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (RIGHT map)
	pTextures->ApplyTexture(5);

	// Desenha face RIGHT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	glPopMatrix();
}