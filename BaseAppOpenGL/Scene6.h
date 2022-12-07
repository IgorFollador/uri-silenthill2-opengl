#pragma once
#include "SceneBaseClass.h"
#include "CTexture.h"
#include "CTimer.h"
#include "CTexto.h"
#include "CCamera.h"
#include "CModel_3DS.h"


class CScene6 : public CSceneBaseClass
{
public:
	CScene6();
	~CScene6(void);


	virtual void MouseMove(void);					// Tratamento de movimento do mouse
	virtual void KeyPressed(void);					// Tratamento de teclas pressionadas
	virtual void KeyDownPressed(WPARAM	wParam);	// Tratamento de teclas pressionadas
	virtual int DrawGLScene(void);					// Função que desenha a cena

	void Draw3DSGrid(float width, float length);
	void DrawAxis();

	void DrawCube(float pX = 0.0f, float pY = 0.0f, float pZ = 0.0f,
		float rX = 0.0f, float rY = 0.0f, float rZ = 0.0f, float angle = 0.0f,
		float sX = 1.0f, float sY = 1.0f, float sZ = 1.0f,
		int texID = -1);

	void CreateSkyBox(float x, float y, float z,
		float width, float height, float length,
		CTexture* pTextures);

	void DrawTree(float pX = 0.0f, float pY = 0.0f, float pZ = 0.0f,
		float sX = 1.0f, float sY = 1.0f, float sZ = 1.0f,
		int texID = -1);
private:

	bool	keys[256];		// Array usado para rotinas do teclado
	bool	active;			// Window Active Flag Set To TRUE By Default
	bool	fullscreen;		// Exibir janela em modo fullscreem (TRUE) ou em janela (FALSE)


	CCamera* pCamera;	// Gerencia câmera OpenGL
	float fDeltaY;				// Rotação da câmera OpenGL no eixo Y
	float fDeltaX;				// Rotação da câmera OpenGL no eixo X

	CTexto* pTexto;	// Objeto que gerencia texto
	CTexture* pTextures;	// Objeto que gerencia texturas
	CTimer* pTimer;	// Objeto que gerencia o timer


	int		iFPS;			// FPS and FPS Counter
	int		iFrames;		// FPS and FPS Counter
	DWORD	ulLastFPS;		// FPS and FPS Counter
	char	szTitle[256];	// FPS and FPS Counter


	bool bIsWireframe;	// Modos Wireframe/Solid
	bool bIsCameraFPS;	// Ativa modo de camera First Person Shooter (true) ou Third Person Shooter (false)

	float fRenderPosY;
	float fTimerPosY;

	// Definindo as propriedades da fonte de luz
	GLfloat LightAmbient[4];
	GLfloat LightDiffuse[4];
	GLfloat LightSpecular[4];
	GLfloat LightPosition[4];

	// Definindo as propriedades do material
	GLfloat MatAmbient[4];
	GLfloat MatDiffuse[4];
	GLfloat MatSpecular[4];
	GLfloat MatShininess;

	float fLampPosX;
	float fLampPosY;
	float fLampPosZ;
	float fMoveRate;


	CModel_3DS* pTerreno;
	CModel_3DS* pFloor;
	CModel_3DS* pSideWalk;
	CModel_3DS* pBathroom;
	CModel_3DS* pTrash;
	CModel_3DS* pBoxes;
	CModel_3DS* pStop;
	CModel_3DS* pPost;
	CModel_3DS* pFence;
	CModel_3DS* pCar;
	bool isNormalMap;
	bool isFob;

};

