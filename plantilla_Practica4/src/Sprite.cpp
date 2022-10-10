#define STB_IMAGE_IMPLEMENTATION

#include "Sprite.h"
#include "stb_image.h"


Sprite::Sprite(const ltex_t* _tex, int _iHframes, int _iVframes)
	: m_texture(_tex),
	m_iHframes(_iHframes),
	m_iVframes(_iVframes)
{
	SetPosition(0, 0);
	SetScale(1, 1);
	SetPivot(0.5f, 0.5f);
}

void Sprite::Update(float _fDeltaTime)
{
}

void Sprite::Draw() const
{
}

void Sprite::SetCallback(CallbackFunc _func)
{
	m_CallbackFunc = _func;
}

const ltex_t* Sprite::GetTexture() const
{
	return m_texture;
}

void Sprite::SetTexture(const ltex_t* _tex, int _iHframes, int _iVframes)
{
	m_texture = _tex;
	m_iHframes = _iHframes;
	m_iVframes = _iVframes;
}

lblend_t Sprite::GetBlend() const
{
	return m_blendMode;
}

void Sprite::SetBlend(lblend_t _mode)
{
	m_blendMode = _mode;
}

float Sprite::GetRed() const
{
	return m_fRed;
}

float Sprite::GetGreen() const
{
	return m_fGreen;
}

float Sprite::GetBlue() const
{
	return m_fBlue;
}

float Sprite::GetAlpha() const
{
	return m_fAlpha;
}

void Sprite::SetColor(float _r, float _g, float _b, float _a)
{
	m_fRed = _r;
	m_fGreen = _g;
	m_fBlue = _b;
	m_fAngle = _a;
}

const MyVec2D& Sprite::GetPosition() const
{
	return m_Position;
}

void Sprite::SetPosition(const MyVec2D& _pos)
{
	m_Position = _pos;
}

void Sprite::SetPosition(float _posX, float _posY)
{
	m_Position.x = _posX;
	m_Position.y = _posY;
}

float Sprite::GetAngle() const
{
	return m_fAngle;
}

void Sprite::SetAngle(float _fAngle)
{
	m_fAngle = _fAngle;
}

const MyVec2D& Sprite::GetScale() const
{
	return m_Scale;
}

void Sprite::SetScale(const MyVec2D& _scale)
{
	m_Scale = _scale;
	//Update Size
	SetSize(m_Scale);
}

void Sprite::SetScale(float _weight, float _height)
{
	m_Scale.x = _weight;
	m_Scale.y = _height;
	//Update Size
	SetSize(m_Scale);
}

MyVec2D Sprite::GetSize() const
{
	return m_Size;
}

void Sprite::SetSize(const MyVec2D& _scale)
{
	MyVec2D auxFrameSize;
	auxFrameSize.x = GetTexture()->width / GetHframes();
	auxFrameSize.y = GetTexture()->height / GetVframes();
	/*float auxFrameSizeX = GetTexture()->width / GetHframes();
	float auxFrameSizeY = GetTexture()->height / GetVframes();*/
	m_Size = auxFrameSize * m_Scale;
}

const MyVec2D& Sprite::GetPivot() const
{
	return m_Pivot;
}

void Sprite::SetPivot(const MyVec2D& _pivot)
{
	m_Pivot = _pivot;
}

void Sprite::SetPivot(float _fPivotX, float _fPivotY)
{
	m_Pivot.x = _fPivotX;
	m_Pivot.y = _fPivotY;
}

int Sprite::GetHframes() const
{
	return m_iHframes;
}

int Sprite::GetVframes() const
{
	return m_iVframes;
}

int Sprite::GetFPS() const
{
	return m_iFPS;
}

void Sprite::SetFPS(int _iFPS)
{
	m_iFPS = _iFPS;
}

float Sprite::GetCurrentFrame() const
{
	return m_fCurrentFrame;
}

void Sprite::SetCurrentFrame(int _iFrame)
{
	m_fCurrentFrame = _iFrame;
}


//
//
////ltex_t* SpriteManager::GenerateTexture(const char* _fileName)
////{
////	int* widthImgSize = new int;
////	int* heightImgSize = new int;
////	//Carga de ficheros de imagen
////	unsigned char* bufferImg = stbi_load(_fileName, widthImgSize, heightImgSize, nullptr, 4); //Datos de la imagen
////	if (!bufferImg)
////	{
////		printf("ERROR! No se ha podido cargar el archivo!");
////
////		return nullptr; //ERROR! No se ha podido cargar el archivo!
////	}
////
////	ltex_t* textureCreated = ltex_alloc(*widthImgSize, *heightImgSize, 1); //Generacion de la textura
////
////	ltex_setpixels(textureCreated, bufferImg); //Volcado de los pixeles en la VRAM
////
////	stbi_image_free(bufferImg); //Eliminar el buffer creado anteriormente, ya he pasado los datos a la imagen que quiero crear (Creada la textura)
////	return  textureCreated;
////}
//
void SpriteManager::LoadTexture(const char* _fileName)
{
	int* widthImgSize = new int;
	int* heightImgSize = new int;
	//Carga de ficheros de imagen
	unsigned char* bufferImg = stbi_load(_fileName, widthImgSize, heightImgSize, nullptr, 4); //Datos de la imagen
	
	if (bufferImg)
	{
		ltex_t* textureCreated = ltex_alloc(*widthImgSize, *heightImgSize, 1); //Generacion de la textura

		ltex_setpixels(textureCreated, bufferImg); //Volcado de los pixeles en la VRAM

		stbi_image_free(bufferImg); //Eliminar el buffer creado anteriormente, ya he pasado los datos a la imagen que quiero crear (Creada la textura)
		//return  textureCreated;
		m_vTextureArray.push_back(textureCreated);
	}
	else
	{
		printf("ERROR! No se ha podido cargar el archivo!");
	}
}

void SpriteManager::UnloadTextures()
{
	for (ltex_t* texLoaded : m_vTextureArray)
	{
		ltex_free(texLoaded);
	}
}
