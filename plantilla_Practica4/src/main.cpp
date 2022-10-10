#define LITE_GFX_IMPLEMENTATION

#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION


#include "main.h"

#include "Font.h"
#include "MyVector2D.h"
#include "stb_image.h"


#include <glfw3.h>
#include <iostream>
#include <vector>



using namespace std;


/* VARIABLES PRACTICA 1*/
int weightWind = 1920;
int heightWind = 1080;
GLFWwindow* myWindow;

double currentTime;
double previousTime;
double deltaTime;
double* delt = nullptr;
double fixedTick = 0.016; // 1/60 para que sean 60 fps
double dangerTicks = 1 / 15;


/* Funciones Practica 2 */

ltex_t* loadTexture(const char* _fileName);



int main()
{
	//Iniciar libreria GFWX
	int inicializarGlfw = glfwInit();

	if (inicializarGlfw == GLFW_TRUE)
	{

		printf("CORRECTA INICIALIZACION GLFW lib\n");
		//Crear Ventana
		myWindow = (glfwCreateWindow(weightWind, heightWind, "HelloWorldText", nullptr, nullptr));

		//Cambiar nombre a la ventana
		glfwSetWindowTitle(myWindow, "Practica3 FerCalderon");

		//Asociar contexto OpenGL a ventana
		glfwMakeContextCurrent(myWindow);

		lgfx_setup2d(weightWind, heightWind);

		MyVec2D myCursorPos;

		previousTime = glfwGetTime();

		//Carga de ficheros de Fuentes


#pragma region LOAD_FONTS

		/* VARIABLES PRACTICA 3*/
		std::vector<FontDrawable*> FontDrawableList;
		const char* text_HelloWorld("Hello, World!");

		//Carga de ficheros de imagen
		FontManager* ptrFontManager = new FontManager();

		Font* auxFont = ptrFontManager->Load("data/SFSlapstickComic.ttf", 50);
		ptrFontManager->m_LoadedFontArray.push_back(auxFont);

		auxFont = ptrFontManager->Load("data/Orange.ttf", 50);
		ptrFontManager->m_LoadedFontArray.push_back(auxFont);

		auxFont = nullptr;


#pragma endregion LOAD_FONTS
		
#pragma region LOAD_TEXTURES

		//ptr Textures 
		/*ltex_t* wall_texture = loadTexture(wall_fileName);
		ltex_t* fire_texture = loadTexture(fire_fileName);
		ltex_t* grille_texture = loadTexture(grille_fileName);
		ltex_t* light_texture = loadTexture(light_fileName);*/


		//END Carga de ficheros de imagen
#pragma endregion LOAD_TEXTURES

		while (glfwWindowShouldClose(myWindow) != 1)
		{


			//Actualizar deltaTiempo
			currentTime = glfwGetTime();
			deltaTime += (currentTime - previousTime);
			previousTime = currentTime;

			while (deltaTime >= fixedTick)
			{

				//std::cout << " LOGIC Loop\n";
				//std::cout << deltaTime << " Es el deltaTime Actual\n";


					//Leer Input de usuario
				if (glfwGetKey(myWindow, GLFW_KEY_ESCAPE))
				{
					glfwSetWindowTitle(myWindow, "Cierra");
					glfwSetWindowShouldClose(myWindow, 1);
				}


				//------------------   UPDATE LOGIC!------------------------------ //////////////////////////////////////////////////
				//CREATE NEW TEXT TO RENDER
				int randomTextSpawn = rand() % 101;
				if (randomTextSpawn == 0)
				{
					//if (FontDrawableList.size() < 5) 
					{

						FontDrawable* auxtext = new FontDrawable(weightWind, (rand() % heightWind + 1));
						auxtext->SetRGB(rand() % 256, rand() % 256, rand() % 256);
						auxtext->SetText(text_HelloWorld);
						auxtext->SetFont(ptrFontManager->m_LoadedFontArray[rand() % 2]);
						float randomSpeed = 20.f + rand() % 181;
						auxtext->SetSpeed(randomSpeed);
						//std::cout << "Creado " << sizeof(auxtext) << "\n";
						std::cout << "Creado unidad " << FontDrawableList.size() << "\n";
						
						FontDrawableList.push_back(auxtext);
					}
				}

				//LOGICA TEXTOS! UPDATE POSITION Y Detectar Limite para eliminar
				for (int i = 0; i < FontDrawableList.size(); i++)
				{
					if (FontDrawableList[i])
					{
						FontDrawableList[i]->UpdatePos(deltaTime);

						if (FontDrawableList[i]->GetPos().x < -400) //Mas o menos es el tamaño del texto, usado para cuando sale de la pantalla
						{
							//std::cout << "Antes contiene " << FontDrawableList.size() << "\n";
							delete FontDrawableList[i];
							FontDrawableList.erase(FontDrawableList.begin() + i);
							//std::cout << "Ahora tiene " << FontDrawableList.size() << "\n";
						}
					}

				}


				if (deltaTime >= dangerTicks)
				{
					deltaTime -= fixedTick;
					//std::cout << "DANGER TIME LOGIC Loop\n";
					//deltaTime = fixedTick;
				}

				deltaTime = 0;

			}

			//---------------------------------RENDER WINDOW-----------------------------------//////

			//std::cout << " Render\n";
			// 
			//Borrar el backbuffer
			lgfx_clearcolorbuffer(1.f, 1.f, 1.f);


			//RENDER TEXTOS*****************************************
			lgfx_setblend(BLEND_ALPHA);
			for (int i = 0; i < FontDrawableList.size(); i++)
			{
				if (FontDrawableList[i])
				{

					lgfx_setcolor(FontDrawableList[i]->GetR() / 255, FontDrawableList[i]->GetG() / 255, FontDrawableList[i]->GetB() / 255, 1);
					FontDrawableList[i]->Draw();
				}
			}

			lgfx_setcolor(1.f, 1.f, 1.f, 1); //Restablecer a color blanco para que no se ponga la pantalla del ultimo color seteado O.o


			//Cambio de buffers
			glfwSwapBuffers(myWindow);

			//Procesar eventos
			glfwPollEvents();

		}

		//Liberar recursos
		/*ltex_free(wall_texture);
		ltex_free(fire_texture);
		ltex_free(grille_texture);
		ltex_free(light_texture);
*/
		//Elimino los obj de palabras (lo que realmente se pinta)
		

		std::cout << "Liberar el array de Fuentes Cargadas  \n";
		for (int i = 0; i < FontDrawableList.size(); i++)
		{
			if (FontDrawableList[i])
			{

			delete FontDrawableList[i];
			FontDrawableList.erase(FontDrawableList.begin() + i);
			}
		}


		//FontDrawableList = nullptr;

		/*for (int i = 0; i < ptrFontManager->m_LoadedFontArray.size(); i++)
		{
			delete ptrFontManager->m_LoadedFontArray[i];
			ptrFontManager->m_LoadedFontArray.erase(ptrFontManager->m_LoadedFontArray.begin() + i);
		}*/

		std::cout << "Liberar ptr FontManager  \n";
		delete ptrFontManager;
		ptrFontManager = nullptr;
		
		//std::cout << "Liberado HelloWorld  \n";
		//delete text_HelloWorld;
		//text_HelloWorld = nullptr;

		std::cout << "Terminar GLFW \n";
		glfwTerminate();

	}
	else
	{
		printf("FALLO AL INICIALIZAR GLFW lib");
		//glfwTerminate(); No libero recursos puesto que no se ha llegado a inicializar la libreria
		return 0;
	}

	std::cout << "Todo liberado, Procedo a cerrar la App \n";
	//Liberar recursos
	//glfwTerminate();
	return 0;
}

ltex_t* loadTexture(const char* _fileName)
{
	int* widthImgSize = new int;
	int* heightImgSize = new int;
	//Carga de ficheros de imagen
	unsigned char* bufferImg = stbi_load(_fileName, widthImgSize, heightImgSize, nullptr, 4); //Datos de la imagen
	if (!bufferImg)
	{
		printf("ERROR! No se ha podido cargar el archivo!");

		return nullptr; //ERROR! No se ha podido cargar el archivo!
	}

	ltex_t* textureCreated = ltex_alloc(*widthImgSize, *heightImgSize, 1); //Generacion de la textura

	ltex_setpixels(textureCreated, bufferImg); //Volcado de los pixeles en la VRAM

	stbi_image_free(bufferImg); //Eliminar el buffer creado anteriormente, ya he pasado los datos a la imagen que quiero crear (Creada la textura)
	return  textureCreated;
}

